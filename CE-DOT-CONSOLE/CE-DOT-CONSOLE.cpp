// CE-DOT-CONSOLE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>

#include "DataParser.h"
#include "SendEmail.h"

using namespace std;

#define REPORTS_LOCAL_DIR   "..\\data_server\\"

class TracsSolution {
public:
    TracsSolution() {}
    ~TracsSolution() {
        finalizeDB();
    }

    void run() {
        // initialize database
        initDB();

        // check reports stored in local directory
        CString strReports = checkReports();

        // report results by email
        if (!strReports.IsEmpty()) {
            email(strReports);
        }
    }

private:
    enum {
        XMLDATA_OK = 0,
        XMLDATA_DOWNLOAD_ERR,
        XMLDATA_PARSE_ERR,
        XMLDATA_URC_DUPLICATE,
        XMLDATA_PARSE_CRASH_DATA_ERR,
        XMLDATA_IMPORT_CRASH_DATA_ERR,
        XMLDATA_PARSE_VEH_DATA_ERR,
        XMLDATA_IMPORT_VEH_DATA_ERR
    };

    _ConnectionPtr  m_pConnection;
    _RecordsetPtr   m_pRecordset;

private:
    int initDB() 
    {
        ::CoInitialize(NULL);

        m_pConnection = NULL;
        m_pRecordset = NULL;

        try {
            m_pConnection.CreateInstance("ADODB.Connection");
        }
        catch (_com_error e) {
            return -1;
        }

        try {
            m_pRecordset.CreateInstance(__uuidof(Recordset));
        }
        catch (_com_error e) {
            return -1;
        }

        return connectDB();
    }

    int finalizeDB()
    {
        closeDB();

        ::CoUninitialize();
        try
        {
            if (m_pRecordset) {
                m_pRecordset.Release();
            }

            if (m_pConnection) {
                m_pConnection->Close();
            }
        }
        catch (_com_error e)
        {
            return 1;
        }

        return 0;
    }

    int connectDB()
    {
        closeDB();

        CString strServerName = _T("LOCALHOST\\SQLEXPRESS");

        CString strConnect;
        strConnect.Format(_T("Provider=SQLOLEDB; \
                            Data Source=%s;\
                            Initial Catalog= DOT; \
                            integrated security=SSPI"), strServerName);
        try
        {
            m_pConnection->Open((_bstr_t)strConnect, "", "", adModeUnknown);
        }
        catch (_com_error e)
        {
            TRACE(_T("Fail to open database: %s\n"), CString((LPCTSTR)e.Description()));
            return 1;
        }

        return 0;
    }

    int closeDB()
    {
        try
        {
            m_pConnection->Close();
        }
        catch (_com_error e)
        {
            TRACE(_T("error: %s\n"), CString((LPCTSTR)e.Description()));
            return 1;
        }

        return 0;
    }

    CString checkReports() 
    {
        CString strReports;

        CStringList strSucceed;
        CStringList strFail;
        CStringList strAttention;

        WIN32_FIND_DATA search_data;
        memset(&search_data, 0, sizeof(search_data));

        HANDLE handle = FindFirstFile(CString(REPORTS_LOCAL_DIR) + _T("/UCR*.xml"), &search_data);
        while (handle != INVALID_HANDLE_VALUE) {
            CString strReportFileName = CString(REPORTS_LOCAL_DIR) + search_data.cFileName;
            if (search_data.cFileName[3] >= '0' && search_data.cFileName[3] <= '9') {

                CDataParser dataParser;
                switch (checkContent(dataParser, strReportFileName)) {
                case XMLDATA_OK:
                    strSucceed.AddTail(dataParser.GetUCRNumber());
                    break;

                default:
                    strFail.AddTail(search_data.cFileName);
                    break;
                }

                CString str = checkReportCriteria(dataParser);
                if (!str.IsEmpty()) {
                    strAttention.AddTail(str);
                }
                else {
                    deleteFromLocal(dataParser.GetUCRNumber());
                }
            }

            if (FindNextFile(handle, &search_data) == FALSE)    break;
        }
        FindClose(handle);

        int totalReports = strSucceed.GetSize() + strFail.GetSize();
        if (0 == totalReports)  return strReports;

        strReports.Format(_T("Total Reports Number: %d\n"), totalReports);
        strReports += _T("Succeeded: ");
        for (POSITION i = strSucceed.GetHeadPosition(); i != NULL; ) {
            strReports += strSucceed.GetNext(i).GetString() + CString("    ");
        }

        strReports += _T("\nFailed: ");
        for (POSITION i = strFail.GetHeadPosition(); i != NULL; ) {
            strReports += strFail.GetNext(i).GetString() + CString("    ");
        }

        strReports += _T("\nNeed Review: ");
        for (POSITION i = strAttention.GetHeadPosition(); i != NULL; ) {
            strReports += strAttention.GetNext(i).GetString() + CString("    ");
        }
        strReports += _T("\n");

        return strReports;
    }

    void deleteFromLocal(CString& ucrNumber)
    {
        TCHAR curDir[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, curDir);
        CString strFiles = CString(REPORTS_LOCAL_DIR) + _T("*") + ucrNumber + _T("*.*");

        WIN32_FIND_DATA search_data;
        memset(&search_data, 0, sizeof(search_data));

        HANDLE handle = FindFirstFile(strFiles, &search_data);
        while (handle != INVALID_HANDLE_VALUE) {
            CString strReportFileName = CString(REPORTS_LOCAL_DIR) + search_data.cFileName;
            DeleteFile(strReportFileName);
            int err = GetLastError();

            if (FindNextFile(handle, &search_data) == FALSE)    break;
        }
        FindClose(handle);
    }

    int checkContent(CDataParser& dataParser, CString& strLocalFileName)
    {
        if (dataParser.Parse(strLocalFileName))
        {
            // parse file failed
            CString strText;
            strText.Format(_T("FAILURE: fail to parse file %s"), strLocalFileName);
            sendOutputMessage(strText);

            return XMLDATA_PARSE_ERR;
        }

        UINT urcNumber;
        dataParser.GetUCRNumber(urcNumber);
        if (urcNumber == 0 || recordExisted(urcNumber))
        {
            // case already exists
            CString strText;
            strText.Format(_T("WARNING: invalid or existed case: %d"), urcNumber);
            sendOutputMessage(strText);

            return XMLDATA_URC_DUPLICATE;
        }

        // get crash data and import into database
        CString strSql;
        if (dataParser.GetSQL_crash(strSql))
        {
            CString strText;
            strText.Format(_T("ERROR: GetSQL_crash failed, file %s"), strLocalFileName);
            sendOutputMessage(strText);

            return XMLDATA_PARSE_CRASH_DATA_ERR;
        }

        if (executeSQL(strSql))
        {
            CString strText;
            strText.Format(_T("ERROR: fail to execute %s from file %s"), strSql, strLocalFileName);
            sendOutputMessage(strText);

            return XMLDATA_IMPORT_CRASH_DATA_ERR;
        }

        // get vehicle data and import into database
        strSql.Empty();
        if (dataParser.GetSQL_vehicle(strSql))
        {
            rollback(urcNumber);

            CString strText;
            strText.Format(_T("ERROR: GetSQL_vehicle failed for file %s"), strLocalFileName);
            sendOutputMessage(strText);

            return XMLDATA_PARSE_VEH_DATA_ERR;
        }

        if (executeSQL(strSql))
        {
            rollback(urcNumber);

            CString strText;
            strText.Format(_T("ERROR: fail to execute %s from file %s"), strSql, strLocalFileName);
            sendOutputMessage(strText);

            return XMLDATA_IMPORT_VEH_DATA_ERR;
        }

        // get occupant data and import into database
        strSql.Empty();
        if (!dataParser.GetSQL_occupant(strSql) && !strSql.IsEmpty())
        {
            executeSQL(strSql);
        }
        else
        {
            // sometimes, we don't have occupant in vehicle
        }

        // success
        CString strText;
        strText.Format(_T("SUCCESS: file %s imported"), strLocalFileName);
        sendOutputMessage(strText);

        return XMLDATA_OK;
    }

    void sendOutputMessage(CString& s) 
    {
        SYSTEMTIME currentTime;
        GetLocalTime(&currentTime);
        char logfile[256];
        snprintf(logfile, sizeof(logfile), "%d-%02d-%02d.log", currentTime.wYear, currentTime.wMonth, currentTime.wDay);

        ofstream log;
        log.open(logfile, ofstream::out | ofstream::app);

        int bodySize = s.GetLength() + 1;
        char* body = new char[bodySize];
        if (body) {
            size_t retSize = bodySize;
            wcstombs_s(&retSize, body, bodySize, s.GetString(), bodySize);

            log << body << endl;

            delete[] body;
        }
    }

    int recordExisted(UINT urcNumber)
    {
        int exist = 0;
        CString strSql;
        strSql.Format(_T("SELECT * FROM [DOT].[dbo].[Acrash2012] WHERE ucrnumber=%d"), urcNumber);

        try
        {
            m_pConnection->CursorLocation = adUseClient;
            m_pRecordset->Open(strSql.GetBuffer(0), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
            if (m_pRecordset->GetRecordCount() > 0)
            {
                exist = 1;
            }
            m_pRecordset->Close();
        }
        catch (_com_error e)
        {
            TRACE(_T("%s\n"), CString((LPCTSTR)e.Description()));
        }

        return exist;
    }

    int executeSQL(const CString& strSql)
    {
        if (strSql.IsEmpty())   return 0;

        try {
            _variant_t recordsAffected;
            HRESULT hr = m_pConnection->Execute((_bstr_t)strSql, &recordsAffected, adCmdText);
            ASSERT(SUCCEEDED(hr));
        }
        catch (_com_error e)
        {
            CString strErr = _T("SQL Err: \n") + CString((LPCTSTR)e.Description()) + _T("-> ") + strSql;
            TRACE(strErr);
            OutputDebugString(strErr);
            return 1;
        }

        return 0;
    }

    int rollback(UINT urcNumber)
    {
        CString strSql;

        strSql.Format(_T("DELETE FROM [dbo].[Acrash2012] WHERE ucrnumber = %d"), urcNumber);
        executeSQL(strSql);

        strSql.Format(_T("DELETE FROM [dbo].[Aoccupant2012] WHERE ucrnumber = %d"), urcNumber);
        executeSQL(strSql);

        strSql.Format(_T("DELETE FROM [dbo].[Avehicle2012] WHERE ucrnumber = %d"), urcNumber);
        executeSQL(strSql);

        return 0;
    }

    CString checkReportCriteria(CDataParser& parser)
    {
        enum {
            FATAL = 1,
            INJURY = 2
        };

        CString strResult;

        // fatality
        if (parser.GetFatalInjury() == FATAL) {
            strResult = "Fatal Injury";
        }
        // animal or train involved
        if (parser.GetClassification() == "ANIMAL") {
            if (!strResult.IsEmpty())  strResult += ", ";
            strResult += "Animal Involved";
        }
        else if (parser.GetClassification() == "RAILROAD TRAIN") {
            if (!strResult.IsEmpty())  strResult += ", ";
            strResult += "Train Involved";
        }
        // Commercial or business
        if (parser.CommercialVehicle()) {
            if (!strResult.IsEmpty())  strResult += ", ";
            strResult += "Commercial Vehicle Involved";
        }
        // state property
        if (parser.StateHighwayPropertyDamage()) {
            if (!strResult.IsEmpty())  strResult += ", ";
            strResult += "State Highway Property Damage Involved";
        }

        if (!strResult.IsEmpty()) {
            strResult = parser.GetUCRNumber() + ": " + strResult;
        }

        return strResult;
    }

public:
    int email(CString& strReports)
    {
        SYSTEMTIME currentTime;
        GetLocalTime(&currentTime);

        CString strTime;
        strTime.Format(_T("\n\n\n%d-%d-%d %d:%d\n"),
            currentTime.wYear,
            currentTime.wMonth,
            currentTime.wDay,
            currentTime.wHour,
            currentTime.wMinute);

        strReports = strReports + strTime;

        // generate local report.
        sendOutputMessage(strReports);

        char body[4096 * 2] = { 0 };
        size_t i = sizeof(body);
        if (i <= strReports.GetLength()) {
            strReports = CString(_T("Email body is too big (>8K), please see log file generated for today.")) + strTime;
        }
        wcstombs_s(&i, body, strReports.GetString(), sizeof(body));

        sendEmail(body);

        return 0;
    }
};

//////////////////////////////////////////////////////////////////////////
int main()
{
    TracsSolution().run();

    return 0;
}

