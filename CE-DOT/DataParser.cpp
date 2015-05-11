#include "stdafx.h"
#include "DataParser.h"


enum {
            E_FORM,
            E_SUMMARY,
            E_VEHICLE,
            E_CONDITIONS,
            E_NARRATIVE,
            E_PROPERTY,
            E_VIOLATION,
            E_CONCULSION,
            E_DIAGRAM, 
            E_LOCATION
};
const char* key_list[] = { 
            "FORM",
            "Summary",
            "Vehicle",
            "Conditions",
            "Narrative",
            "Property",
            "Violation",
            "Conclusion",
            "Diagram", 
            "Location"
};

CDataParser::CDataParser()
{
}


CDataParser::~CDataParser()
{
}


void CDataParser::Reset()
{
    m_fileContent.Reset();
    m_strFileName.Empty();
}

int CDataParser::Parse(CString& strLocalFileName)
{
    Reset();

    // load file
    char fileName[MAX_PATH];
    wcstombs(fileName, strLocalFileName.GetString(), MAX_PATH);

    TiXmlDocument doc(fileName);
    if (!doc.LoadFile()) 
    {
        return 1;
    }
    TiXmlElement* root = doc.RootElement();
    const char* key = root->Value();
    if (-1 == IsKeyElement(key)) 
    {
        // error format
        return 1;
    }

    TiXmlNode* child = root->FirstChildElement();

    while (child) 
    {
        key = child->Value();

        if (-1 != IsKeyElement(key)) 
        {
            DispatchEntity(child);
        }
        else 
        {
            const char* value = child->FirstChild()->Value();
            TRACE("K = %s, V = %s\n", key, value);
            FillForm(key, value);
        }
        child = child->NextSibling();
    }

    m_strFileName = strLocalFileName;
    return 0;
}

int CDataParser::IsKeyElement(const char* key)
{
    for (size_t i = 0; i < sizeof(key_list) / sizeof(const char*); ++i) 
    {
        if (!_strnicmp(key, key_list[i], strlen(key_list[i])))
        {
            if (strlen(key) > strlen(key_list[i]))
            {
                if (key[strlen(key_list[i])] == '_')
                {
                    return i;
                }
            }
            else
            {
                return i;
            }
        }
    }

    return -1;
}

int CDataParser::DispatchEntity(TiXmlNode* child)
{
    const char* key = child->Value();

    switch (IsKeyElement(key)) 
    {
    case E_SUMMARY:
        FillSummary(child);
        break;

    case E_VEHICLE:
        FillVehicles(child);
        break;

    case E_CONDITIONS:
        FillConditions(child);
        break;

    case E_NARRATIVE:
        FillNarrative(child);
        break;

    case E_PROPERTY:
        FillProperties(child);
        break;

    case E_VIOLATION:
        FillViolations(child);
        break;

    case E_CONCULSION:
        FillConclusion(child);
        break;

    case E_DIAGRAM:
        FillDiagram(child);
        break;

    case E_LOCATION:
        FillLocation(child);
        break;

    default:
        break;

    }

    return 0;
}

int CDataParser::FillForm(const char* key, const char* value)
{
    if (!_stricmp(key, "CaseNumber"))
    {
        m_fileContent.CaseNumber = atoi(value);
    }
    else if (!_stricmp(key, "OfficerAtScene"))
    {
        m_fileContent.OfficerAtScene = value;
    }
    else if (!_stricmp(key, "BadgeNumber"))
    {
        m_fileContent.BadgeNumber = atoi(value);
    }
    else if (!_stricmp(key, "Agency"))
    {
        m_fileContent.Agency = atoi(value);
    }
    else if (!_stricmp(key, "NumberofVehicles"))
    {
        m_fileContent.NumberofVehicles = atoi(value);
    }
    else if (!_stricmp(key, "NumberofDrawings"))
    {
        m_fileContent.NumberofDrawings = atoi(value);
    }
    else if (!_stricmp(key, "PropertyDamage"))
    {
        m_fileContent.PropertyDamage = atoi(value);
    }
    else if (!_stricmp(key, "WitnessPresent"))
    {
        m_fileContent.WitnessPresent = atoi(value);
    }

    return 0;
}

int CDataParser::FillSummary(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillSummary(key, value);
        }

        child = child->NextSibling();
    }

    return 0;
}

int CDataParser::FillSummary(const char* key, const char* value)
{
    if (!_stricmp(key, "Agency"))
    {
        m_fileContent.summary.Agency = value;
    }
    else if (!_stricmp(key, "UCRNumber"))
    {
        m_fileContent.summary.UCRNumber = atoi(value);
    }
    else if (!_stricmp(key, "PrivateProperty"))
    {
        m_fileContent.summary.PrivateProperty = atoi(value);
    }
    else if (!_stricmp(key, "Fatal_Injury"))
    {
        m_fileContent.summary.Fatal_Injury = atoi(value);
    }
    else if (!_stricmp(key, "Hit_Run"))
    {
        m_fileContent.summary.Hit_Run = atoi(value);
    }
    else if (!_stricmp(key, "NMDOTNumber"))
    {
        m_fileContent.summary.NMDOTNumber = atoi(value);
    }
    else if (!_stricmp(key, "CADNumber"))
    {
        m_fileContent.summary.CADNumber = atoi(value);
    }
    else if (!_stricmp(key, "CrashDate"))
    {
        m_fileContent.summary.CrashDate = value;
    }
    else if (!_stricmp(key, "MilitaryTime"))
    {
        m_fileContent.summary.MilitaryTime = value;
    }
    else if (!_stricmp(key, "County"))
    {
        m_fileContent.summary.County = atoi(value);
    }
    else if (!_stricmp(key, "City"))
    {
        m_fileContent.summary.City = value;
    }
    else if (!_stricmp(key, "TribalJurisdiction"))
    {
        m_fileContent.summary.TribalJurisdiction = value;
    }
    else if (!_stricmp(key, "WeekDay"))
    {
        WeekDayString2Int(value, m_fileContent.summary.WeekDay);
    }
    else if (!_stricmp(key, "STREETA"))
    {
        m_fileContent.summary.STREETA = value;
    }
    else if (!_stricmp(key, "INTERSECTING_STREETB"))
    {
        m_fileContent.summary.INTERSECTING_STREETB = value;
    }
    else if (!_stricmp(key, "Measurement"))
    {
        m_fileContent.summary.Measurement = atoi(value);
    }
    else if (!_stricmp(key, "MeasurementUnit"))
    {
        m_fileContent.summary.MeasurementUnit = value;
    }
    else if (!_stricmp(key, "DirectionFromLandmark"))
    {
        m_fileContent.summary.DirectionFromLandmark = value;
    }
    else if (!_stricmp(key, "Landmark"))
    {
        m_fileContent.summary.Landmark = value;
    }
    else if (!_stricmp(key, "Milepost"))
    {
        m_fileContent.summary.Milepost = value;
    }
    else if (!_stricmp(key, "Latitude"))
    {
        m_fileContent.summary.Latitude = value;
    }
    else if (!_stricmp(key, "Longitude"))
    {
        m_fileContent.summary.Longitude = value;
    }
    else if (!_stricmp(key, "CRASHOCCURRENCE"))
    {
        m_fileContent.summary.CRASHOCCURRENCE = value;
    }
    else if (!_stricmp(key, "CrashClassification"))
    {
        m_fileContent.summary.CrashClassification = value;
    }
    else if (!_stricmp(key, "AnalysisCode"))
    {
        m_fileContent.summary.Agency = value;
    }
    else if (!_stricmp(key, "Lighting"))
    {
        m_fileContent.summary.Lighting = value;
    }
    else if (!_stricmp(key, "WEATHER"))
    {
        m_fileContent.summary.WEATHER = value;
    }
    else if (!_stricmp(key, "RoadCharacter"))
    {
        m_fileContent.summary.RoadCharacter = value;
    }
    else if (!_stricmp(key, "RoadGrade"))
    {
        m_fileContent.summary.RoadGrade = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillVehicles(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillVehicles(key, value);
        }

        child = child->NextSibling();
    }

    return 0;
}

int CDataParser::FillVehicles(const char* key, const char* value)
{
    if (!_strnicmp(key, "vVehNo", strlen("vVehNo")))
    {
        ASSERT(key[strlen("vVehNo")] == '_');
        int i = atoi(&key[strlen("vVehNo") + 1]) - 1;
        m_fileContent.vehicles[i].vVehNo = atoi(value);
    }
    else if (!_strnicmp(key, "DrSex", strlen("DrSex")))
    {
        ASSERT(key[strlen("DrSex")] == '_');
        int i = atoi(&key[strlen("DrSex") + 1]) - 1;
        m_fileContent.vehicles[i].DrSex = value;
    }
    else if (!_strnicmp(key, "DrRace", strlen("DrRace")))
    {
        ASSERT(key[strlen("DrRace")] == '_');
        int i = atoi(&key[strlen("DrRace") + 1]) - 1;
        m_fileContent.vehicles[i].DrRace = value;
    }
    else if (!_strnicmp(key, "VehDirection", strlen("VehDirection")))
    {
        ASSERT(key[strlen("VehDirection")] == '_');
        int i = atoi(&key[strlen("VehDirection") + 1]) - 1;
        m_fileContent.vehicles[i].VehDirection = value;
    }
    else if (!_strnicmp(key, "StreetOn", strlen("StreetOn")))
    {
        ASSERT(key[strlen("StreetOn")] == '_');
        int i = atoi(&key[strlen("StreetOn") + 1]) - 1;
        m_fileContent.vehicles[i].StreetOn = value;
    }
    else if (!_strnicmp(key, "LeftScene", strlen("LeftScene")))
    {
        ASSERT(key[strlen("LeftScene")] == '_');
        int i = atoi(&key[strlen("LeftScene") + 1]) - 1;
        m_fileContent.vehicles[i].LeftScene = value;
    }
    else if (!_strnicmp(key, "UnitType", strlen("UnitType")))
    {
        ASSERT(key[strlen("UnitType")] == '_');
        int i = atoi(&key[strlen("UnitType") + 1]) - 1;
        m_fileContent.vehicles[i].UnitType = value;
    }
    else if (!_strnicmp(key, "PostedSpeed", strlen("PostedSpeed")))
    {
        ASSERT(key[strlen("PostedSpeed")] == '_');
        int i = atoi(&key[strlen("PostedSpeed") + 1]) - 1;
        m_fileContent.vehicles[i].PostedSpeed = atoi(value);
    }
    else if (!_strnicmp(key, "SafeSpeed", strlen("SafeSpeed")))
    {
        ASSERT(key[strlen("SafeSpeed")] == '_');
        int i = atoi(&key[strlen("SafeSpeed") + 1]) - 1;
        m_fileContent.vehicles[i].SafeSpeed = atoi(value);
    }
    else if (!_strnicmp(key, "DRFIRSTNAME", strlen("DRFIRSTNAME")))
    {
        ASSERT(key[strlen("DRFIRSTNAME")] == '_');
        int i = atoi(&key[strlen("DRFIRSTNAME") + 1]) - 1;
        m_fileContent.vehicles[i].DRFIRSTNAME = value;
    }
    else if (!_strnicmp(key, "DRLASTNAME", strlen("DRLASTNAME")))
    {
        ASSERT(key[strlen("DRLASTNAME")] == '_');
        int i = atoi(&key[strlen("DRLASTNAME") + 1]) - 1;
        m_fileContent.vehicles[i].DRLASTNAME = value;
    }
    else if (!_strnicmp(key, "DRMIDDLENAME", strlen("DRMIDDLENAME")))
    {
        ASSERT(key[strlen("DRMIDDLENAME")] == '_');
        int i = atoi(&key[strlen("DRMIDDLENAME") + 1]) - 1;
        m_fileContent.vehicles[i].DRMIDDLENAME = value;
    }
    else if (!_strnicmp(key, "DRADDRESS", strlen("DRADDRESS")))
    {
        ASSERT(key[strlen("DRADDRESS")] == '_');
        int i = atoi(&key[strlen("DRADDRESS") + 1]) - 1;
        m_fileContent.vehicles[i].DRADDRESS = value;
    }
    else if (!_strnicmp(key, "DLNUMBER", strlen("DLNUMBER")))
    {
        ASSERT(key[strlen("DLNUMBER")] == '_');
        int i = atoi(&key[strlen("DLNUMBER") + 1]) - 1;
        m_fileContent.vehicles[i].DLNUMBER = value;
    }
    else if (!_strnicmp(key, "DLState", strlen("DLState")))
    {
        ASSERT(key[strlen("DLState")] == '_');
        int i = atoi(&key[strlen("DLState") + 1]) - 1;
        m_fileContent.vehicles[i].DLState = value;
    }
    else if (!_strnicmp(key, "DLType", strlen("DLType")))
    {
        ASSERT(key[strlen("DLType")] == '_');
        int i = atoi(&key[strlen("DLType") + 1]) - 1;
        m_fileContent.vehicles[i].DLType = value;
    }
    else if (!_strnicmp(key, "DLStatus", strlen("DLStatus")))
    {
        ASSERT(key[strlen("DLStatus")] == '_');
        int i = atoi(&key[strlen("DLStatus") + 1]) - 1;
        m_fileContent.vehicles[i].DLStatus = value;
    }
    else if (!_strnicmp(key, "DLRestrictions", strlen("DLRestrictions")))
    {
        ASSERT(key[strlen("DLRestrictions")] == '_');
        int i = atoi(&key[strlen("DLRestrictions") + 1]) - 1;
        m_fileContent.vehicles[i].DLRestrictions = value;
    }
    else if (!_strnicmp(key, "DLEndorsements", strlen("DLEndorsements")))
    {
        ASSERT(key[strlen("DLEndorsements")] == '_');
        int i = atoi(&key[strlen("DLEndorsements") + 1]) - 1;
        m_fileContent.vehicles[i].DLEndorsements = value;
    }
    else if (!_strnicmp(key, "DLExpires", strlen("DLExpires")))
    {
        ASSERT(key[strlen("DLExpires")] == '_');
        int i = atoi(&key[strlen("DLExpires") + 1]) - 1;
        m_fileContent.vehicles[i].DLExpires = value;
    }
    else if (!_strnicmp(key, "DRCITY", strlen("DRCITY")))
    {
        ASSERT(key[strlen("DRCITY")] == '_');
        int i = atoi(&key[strlen("DRCITY") + 1]) - 1;
        m_fileContent.vehicles[i].DRCITY = value;
    }
    else if (!_strnicmp(key, "DRSTATE", strlen("DRSTATE")))
    {
        ASSERT(key[strlen("DRSTATE")] == '_');
        int i = atoi(&key[strlen("DRSTATE") + 1]) - 1;
        m_fileContent.vehicles[i].DRSTATE = value;
    }
    else if (!_strnicmp(key, "DRZIP", strlen("DRZIP")))
    {
        ASSERT(key[strlen("DRZIP")] == '_');
        int i = atoi(&key[strlen("DRZIP") + 1]) - 1;
        m_fileContent.vehicles[i].DRZIP = atoi(value);
    }
    else if (!_strnicmp(key, "DRPHONE", strlen("DRPHONE")))
    {
        ASSERT(key[strlen("DRPHONE")] == '_');
        int i = atoi(&key[strlen("DRPHONE") + 1]) - 1;
        m_fileContent.vehicles[i].DRPHONE = value;
    }
    else if (!_strnicmp(key, "DLDoB", strlen("DLDoB")))
    {
        ASSERT(key[strlen("DLDoB")] == '_');
        int i = atoi(&key[strlen("DLDoB") + 1]) - 1;
        m_fileContent.vehicles[i].DLDoB = value;
    }
    else if (!_strnicmp(key, "DrOccupation", strlen("DrOccupation")))
    {
        ASSERT(key[strlen("DrOccupation")] == '_');
        int i = atoi(&key[strlen("DrOccupation") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrOccupation = value;
    }
    else if (!_strnicmp(key, "DRSeatPos", strlen("DRSeatPos")))
    {
        ASSERT(key[strlen("DRSeatPos")] == '_');
        int i = atoi(&key[strlen("DRSeatPos") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DRSeatPos = value;
    }
    else if (!_strnicmp(key, "DRSSN", strlen("DRSSN")))
    {
        ASSERT(key[strlen("DRSSN")] == '_');
        int i = atoi(&key[strlen("DRSSN") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DRSSN = value;
    }
    else if (!_strnicmp(key, "DrAge", strlen("DrAge")))
    {
        ASSERT(key[strlen("DrAge")] == '_');
        int i = atoi(&key[strlen("DrAge") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrAge = atoi(value);
    }
    else if (!_strnicmp(key, "DrSex", strlen("DrSex")))
    {
        ASSERT(key[strlen("DrSex")] == '_');
        int i = atoi(&key[strlen("DrSex") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrSex = value;
    }
    else if (!_strnicmp(key, "DrRace", strlen("DrRace")))
    {
        ASSERT(key[strlen("DrRace")] == '_');
        int i = atoi(&key[strlen("DrRace") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrRace = value;
    }
    else if (!_strnicmp(key, "DrInjuryCode", strlen("DrInjuryCode")))
    {
        ASSERT(key[strlen("DrInjuryCode")] == '_');
        int i = atoi(&key[strlen("DrInjuryCode") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrInjuryCode = value;
    }
    else if (!_strnicmp(key, "DROPCODE", strlen("DROPCODE")))
    {
        ASSERT(key[strlen("DROPCODE")] == '_');
        int i = atoi(&key[strlen("DROPCODE") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DROPCODE = value;
    }
    else if (!_strnicmp(key, "DrOPProperlyUsed", strlen("DrOPProperlyUsed")))
    {
        ASSERT(key[strlen("DrOPProperlyUsed")] == '_');
        int i = atoi(&key[strlen("DrOPProperlyUsed") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrOPProperlyUsed = value;
    }
    else if (!_strnicmp(key, "DrAirbagDeployed", strlen("DrAirbagDeployed")))
    {
        ASSERT(key[strlen("DrAirbagDeployed")] == '_');
        int i = atoi(&key[strlen("DrAirbagDeployed") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrAirbagDeployed = value;
    }
    else if (!_strnicmp(key, "DrEjected", strlen("DrEjected")))
    {
        ASSERT(key[strlen("DrEjected")] == '_');
        int i = atoi(&key[strlen("DrEjected") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrEjected = value;
    }
    else if (!_strnicmp(key, "DrEMSNum", strlen("DrEMSNum")))
    {
        ASSERT(key[strlen("DrEMSNum")] == '_');
        int i = atoi(&key[strlen("DrEMSNum") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrEMSNum = value;
    }
    else if (!_strnicmp(key, "DrMedTrans", strlen("DrMedTrans")))
    {
        ASSERT(key[strlen("DrMedTrans")] == '_');
        int i = atoi(&key[strlen("DrMedTrans") + 1]) - 1;
        m_fileContent.vehicles[i].Driver.DrMedTrans = value;
    }
    else if (!_strnicmp(key, "oSeatPos", strlen("oSeatPos")))
    {
        int i;
        int j = 0;
        if (key[strlen("oSeatPos")] != '_')
        {
            i = atoi(&key[strlen("oSeatPos?_")]) - 1;
            j = atoi(&key[strlen("oSeatPos")]);
        }
        else
        {
            i = atoi(&key[strlen("oSeatPos_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oSeatPos = value;
    }
    else if (!_strnicmp(key, "oLastName", strlen("oLastName")))
    {
        int i;
        int j = 0;
        if (key[strlen("oLastName")] != '_')
        {
            i = atoi(&key[strlen("oLastName?_")]) - 1;
            j = atoi(&key[strlen("oLastName")]);
        }
        else
        {
            i = atoi(&key[strlen("oLastName_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oLastName = value;
    }
    else if (!_strnicmp(key, "oFirstName", strlen("oFirstName")))
    {
        int i;
        int j = 0;
        if (key[strlen("oFirstName")] != '_')
        {
            i = atoi(&key[strlen("oFirstName?_")]) - 1;
            j = atoi(&key[strlen("oFirstName")]);
        }
        else
        {
            i = atoi(&key[strlen("oFirstName_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oFirstName = value;
    }
    else if (!_strnicmp(key, "oMiddleName", strlen("oMiddleName")))
    {
        int i;
        int j = 0;
        if (key[strlen("oMiddleName")] != '_')
        {
            i = atoi(&key[strlen("oMiddleName?_")]) - 1;
            j = atoi(&key[strlen("oMiddleName")]);
        }
        else
        {
            i = atoi(&key[strlen("oMiddleName_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oMiddleName = value;
    }
    else if (!_strnicmp(key, "oAge", strlen("oAge")))
    {
        int i;
        int j = 0;
        if (key[strlen("oAge")] != '_')
        {
            i = atoi(&key[strlen("oAge?_")]) - 1;
            j = atoi(&key[strlen("oAge")]);
        }
        else
        {
            i = atoi(&key[strlen("oAge_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oAge = atoi(value);
    }
    else if (!_strnicmp(key, "oSex", strlen("oSex")))
    {
        int i;
        int j = 0;
        if (key[strlen("oSex")] != '_')
        {
            i = atoi(&key[strlen("oSex?_")]) - 1;
            j = atoi(&key[strlen("oSex")]);
        }
        else
        {
            i = atoi(&key[strlen("oSex_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oSex = value;
    }
    else if (!_strnicmp(key, "oRace", strlen("oRace")))
    {
        int i;
        int j = 0;
        if (key[strlen("oRace")] != '_')
        {
            i = atoi(&key[strlen("oRace?_")]) - 1;
            j = atoi(&key[strlen("oRace")]);
        }
        else
        {
            i = atoi(&key[strlen("oRace_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oRace = value;
    }
    else if (!_strnicmp(key, "oInjuryCode", strlen("oInjuryCode")))
    {
        int i;
        int j = 0;
        if (key[strlen("oInjuryCode")] != '_')
        {
            i = atoi(&key[strlen("oInjuryCode?_")]) - 1;
            j = atoi(&key[strlen("oInjuryCode")]);
        }
        else
        {
            i = atoi(&key[strlen("oInjuryCode_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oInjuryCode = value;
    }
    else if (!_strnicmp(key, "oOPCode", strlen("oOPCode")))
    {
        int i;
        int j = 0;
        if (key[strlen("oOPCode")] != '_')
        {
            i = atoi(&key[strlen("oOPCode?_")]) - 1;
            j = atoi(&key[strlen("oOPCode")]);
        }
        else
        {
            i = atoi(&key[strlen("oOPCode_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oOPCode = value;
    }
    else if (!_strnicmp(key, "OOPPROPERLYUSED", strlen("OOPPROPERLYUSED")))
    {
        int i;
        int j = 0;
        if (key[strlen("OOPPROPERLYUSED")] != '_')
        {
            i = atoi(&key[strlen("OOPPROPERLYUSED?_")]) - 1;
            j = atoi(&key[strlen("OOPPROPERLYUSED")]);
        }
        else
        {
            i = atoi(&key[strlen("OOPPROPERLYUSED_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].OOPPROPERLYUSED = value;
    }
    else if (!_strnicmp(key, "oAirBagDeploy", strlen("oAirBagDeploy")))
    {
        int i;
        int j = 0;
        if (key[strlen("oAirBagDeploy")] != '_')
        {
            i = atoi(&key[strlen("oAirBagDeploy?_")]) - 1;
            j = atoi(&key[strlen("oAirBagDeploy")]);
        }
        else
        {
            i = atoi(&key[strlen("oAirBagDeploy_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oAirBagDeploy = value;
    }
    else if (!_strnicmp(key, "oEjected", strlen("oEjected")))
    {
        int i;
        int j = 0;
        if (key[strlen("oEjected")] != '_')
        {
            i = atoi(&key[strlen("oEjected?_")]) - 1;
            j = atoi(&key[strlen("oEjected")]);
        }
        else
        {
            i = atoi(&key[strlen("oEjected_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oEjected = value;
    }
    else if (!_strnicmp(key, "oEMSNum", strlen("oEMSNum")))
    {
        int i;
        int j = 0;
        if (key[strlen("oEMSNum")] != '_')
        {
            i = atoi(&key[strlen("oEMSNum?_")]) - 1;
            j = atoi(&key[strlen("oEMSNum")]);
        }
        else
        {
            i = atoi(&key[strlen("oEMSNum_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oEMSNum = value;
    }
    else if (!_strnicmp(key, "oMedTrans", strlen("oMedTrans")))
    {
        int i;
        int j = 0;
        if (key[strlen("oMedTrans")] != '_')
        {
            i = atoi(&key[strlen("oMedTrans?_")]) - 1;
            j = atoi(&key[strlen("oMedTrans")]);
        }
        else
        {
            i = atoi(&key[strlen("oMedTrans_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oMedTrans = value;
    }
    else if (!_strnicmp(key, "oAddress", strlen("oAddress")))
    {
        int i;
        int j = 0;
        if (key[strlen("oAddress")] != '_')
        {
            i = atoi(&key[strlen("oAddress?_")]) - 1;
            j = atoi(&key[strlen("oAddress")]);
        }
        else
        {
            i = atoi(&key[strlen("oAddress_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oAddress = value;
    }
    else if (!_strnicmp(key, "oCity", strlen("oCity")))
    {
        int i;
        int j = 0;
        if (key[strlen("oCity")] != '_')
        {
            i = atoi(&key[strlen("oCity?_")]) - 1;
            j = atoi(&key[strlen("oCity")]);
        }
        else
        {
            i = atoi(&key[strlen("oCity_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oCity = value;
    }
    else if (!_strnicmp(key, "oState", strlen("oState")))
    {
        int i;
        int j = 0;
        if (key[strlen("oState")] != '_')
        {
            i = atoi(&key[strlen("oState?_")]) - 1;
            j = atoi(&key[strlen("oState")]);
        }
        else
        {
            i = atoi(&key[strlen("oState_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oState = value;
    }
    else if (!_strnicmp(key, "oZip", strlen("oZip")))
    {
        int i;
        int j = 0;
        if (key[strlen("oZip")] != '_')
        {
            i = atoi(&key[strlen("oZip?_")]) - 1;
            j = atoi(&key[strlen("oZip")]);
        }
        else
        {
            i = atoi(&key[strlen("oZip_")]) - 1;
        }
        m_fileContent.vehicles[i].Occupant[j].oZip = value;
    }
    else if (!_strnicmp(key, "veYear", strlen("veYear")))
    {
        ASSERT(key[strlen("veYear")] == '_');
        int i = atoi(&key[strlen("veYear") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.veYear = atoi(value);
    }
    else if (!_strnicmp(key, "VeMake", strlen("VeMake")))
    {
        ASSERT(key[strlen("VeMake")] == '_');
        int i = atoi(&key[strlen("VeMake") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeMake = value;
    }
    else if (!_strnicmp(key, "VeColor", strlen("VeColor")))
    {
        ASSERT(key[strlen("VeColor")] == '_');
        int i = atoi(&key[strlen("VeColor") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeColor = value;
    }
    else if (!_strnicmp(key, "VeBodystyle", strlen("VeBodystyle")))
    {
        ASSERT(key[strlen("VeBodystyle")] == '_');
        int i = atoi(&key[strlen("VeBodystyle") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeBodystyle = value;
    }
    else if (!_strnicmp(key, "VeCargoBody", strlen("VeCargoBody")))
    {
        ASSERT(key[strlen("VeCargoBody")] == '_');
        int i = atoi(&key[strlen("VeCargoBody") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeCargoBody = value;
    }
    else if (!_strnicmp(key, "VeUse1", strlen("VeUse1")))
    {
        ASSERT(key[strlen("VeUse1")] == '_');
        int i = atoi(&key[strlen("VeUse1") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeUse1 = value;
    }
    else if (!_strnicmp(key, "VeUse2", strlen("VeUse2")))
    {
        ASSERT(key[strlen("VeUse2")] == '_');
        int i = atoi(&key[strlen("VeUse2") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeUse2 = value;
    }
    else if (!_strnicmp(key, "ICCCarrierCode", strlen("ICCCarrierCode")))
    {
        ASSERT(key[strlen("ICCCarrierCode")] == '_');
        int i = atoi(&key[strlen("ICCCarrierCode") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.ICCCarrierCode = value;
    }
    else if (!_strnicmp(key, "VELICPLATEREGYR", strlen("VELICPLATEREGYR")))
    {
        ASSERT(key[strlen("VELICPLATEREGYR")] == '_');
        int i = atoi(&key[strlen("VELICPLATEREGYR") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VELICPLATEREGYR = value;
    }
    else if (!_strnicmp(key, "VELICPLATESTATE", strlen("VELICPLATESTATE")))
    {
        ASSERT(key[strlen("VELICPLATESTATE")] == '_');
        int i = atoi(&key[strlen("VELICPLATESTATE") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VELICPLATESTATE = value;
    }
    else if (!_strnicmp(key, "VELICPLATENUM", strlen("VELICPLATENUM")))
    {
        ASSERT(key[strlen("VELICPLATENUM")] == '_');
        int i = atoi(&key[strlen("VELICPLATENUM") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VELICPLATENUM = value;
    }
    else if (!_strnicmp(key, "veVin", strlen("veVin")))
    {
        ASSERT(key[strlen("veVin")] == '_');
        int i = atoi(&key[strlen("veVin") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.veVin = value;
    }
    else if (!_strnicmp(key, "veTowedBy", strlen("veTowedBy")))
    {
        ASSERT(key[strlen("veTowedBy")] == '_');
        int i = atoi(&key[strlen("veTowedBy") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.veTowedBy = value;
    }
    else if (!_strnicmp(key, "veTowedTo", strlen("veTowedTo")))
    {
        ASSERT(key[strlen("veTowedTo")] == '_');
        int i = atoi(&key[strlen("veTowedTo") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.veTowedTo = value;
    }
    else if (!_strnicmp(key, "VeTowedDisabled", strlen("VeTowedDisabled")))
    {
        ASSERT(key[strlen("VeTowedDisabled")] == '_');
        int i = atoi(&key[strlen("VeTowedDisabled") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeTowedDisabled = value;
    }
    else if (!_strnicmp(key, "VeTowed", strlen("VeTowed")))
    {
        ASSERT(key[strlen("VeTowed")] == '_');
        int i = atoi(&key[strlen("VeTowed") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeTowed = value;
    }
    else if (!_strnicmp(key, "VeDamageSeverity", strlen("VeDamageSeverity")))
    {
        ASSERT(key[strlen("VeDamageSeverity")] == '_');
        int i = atoi(&key[strlen("VeDamageSeverity") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageSeverity = value;
    }
    else if (!_strnicmp(key, "VeDamageExtent", strlen("VeDamageExtent")))
    {
        ASSERT(key[strlen("VeDamageExtent")] == '_');
        int i = atoi(&key[strlen("VeDamageExtent") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageExtent = value;
    }
    else if (!_strnicmp(key, "VeDamageAll", strlen("VeDamageAll")))
    {
        ASSERT(key[strlen("VeDamageAll")] == '_');
        int i = atoi(&key[strlen("VeDamageAll") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageAll = atoi(value);
    }
    else if (!_strnicmp(key, "VeDamageTop", strlen("VeDamageTop")))
    {
        ASSERT(key[strlen("VeDamageTop")] == '_');
        int i = atoi(&key[strlen("VeDamageTop") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageTop = atoi(value);
    }
    else if (!_strnicmp(key, "VeDamageUndercarriage", strlen("VeDamageUndercarriage")))
    {
        ASSERT(key[strlen("VeDamageUndercarriage")] == '_');
        int i = atoi(&key[strlen("VeDamageUndercarriage") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageUndercarriage = atoi(value);
    }
    else if (!_strnicmp(key, "VeDamageNone", strlen("VeDamageNone")))
    {
        ASSERT(key[strlen("VeDamageNone")] == '_');
        int i = atoi(&key[strlen("VeDamageNone") + 1]) - 1;
        m_fileContent.vehicles[i].Vehicle.VeDamageNone = atoi(value);
    }
    else if (!_strnicmp(key, "VeDamage", strlen("VeDamage")))
    {
        int i;
        int j;
        char key_buf[64];
        memcpy(key_buf, key, strlen(key));
        if (key[strlen("VeDamage?")] == '_')
        {
            i = atoi(&key[strlen("VeDamage?_")]) - 1;
            key_buf[strlen("VeDamage??")] = 0;
            j = atoi(&key_buf[strlen("VeDamage")]) - 1;
        }
        else if (key[strlen("VeDamage??")] == '_')
        {
            i = atoi(&key[strlen("VeDamage??_")]) - 1;
            key_buf[strlen("VeDamage??")] = 0;
            j = atoi(&key_buf[strlen("VeDamage")]) - 1;
        }
        else
        {
            ASSERT(0);
        }
        m_fileContent.vehicles[i].Vehicle.VeDamage[j] = atoi(value);
    }
    else if (!_strnicmp(key, "GrossVehicleWeight", strlen("GrossVehicleWeight")))
    {
        ASSERT(key[strlen("GrossVehicleWeight")] == '_');
        int i = atoi(&key[strlen("GrossVehicleWeight") + 1]) - 1;
        m_fileContent.vehicles[i].GrossVehicleWeight = value;
    }
    else if (!_strnicmp(key, "HazmatPlacard", strlen("HazmatPlacard")))
    {
        ASSERT(key[strlen("HazmatPlacard")] == '_');
        int i = atoi(&key[strlen("HazmatPlacard") + 1]) - 1;
        m_fileContent.vehicles[i].HazmatPlacard = value;
    }
    else if (!_strnicmp(key, "HazmatReleased", strlen("HazmatReleased")))
    {
        ASSERT(key[strlen("HazmatReleased")] == '_');
        int i = atoi(&key[strlen("HazmatReleased") + 1]) - 1;
        m_fileContent.vehicles[i].HazmatReleased = value;
    }
    else if (!_strnicmp(key, "USDOTNum", strlen("USDOTNum")))
    {
        ASSERT(key[strlen("USDOTNum")] == '_');
        int i = atoi(&key[strlen("USDOTNum") + 1]) - 1;
        m_fileContent.vehicles[i].USDOTNum = atoi(value);
    }
    else if (!_strnicmp(key, "InterstateCarrier", strlen("InterstateCarrier")))
    {
        ASSERT(key[strlen("InterstateCarrier")] == '_');
        int i = atoi(&key[strlen("InterstateCarrier") + 1]) - 1;
        m_fileContent.vehicles[i].InterstateCarrier = value;
    }
    else if (!_strnicmp(key, "NumberofAxles", strlen("NumberofAxles")))
    {
        ASSERT(key[strlen("NumberofAxles")] == '_');
        int i = atoi(&key[strlen("NumberofAxles") + 1]) - 1;
        m_fileContent.vehicles[i].NumberofAxles = value;
    }
    else if (!_strnicmp(key, "HazmatName", strlen("HazmatName")))
    {
        ASSERT(key[strlen("HazmatName")] == '_');
        int i = atoi(&key[strlen("HazmatName") + 1]) - 1;
        m_fileContent.vehicles[i].HazmatName = value;
    }
    else if (!_strnicmp(key, "CarrierName", strlen("CarrierName")))
    {
        ASSERT(key[strlen("CarrierName")] == '_');
        int i = atoi(&key[strlen("CarrierName") + 1]) - 1;
        m_fileContent.vehicles[i].CarrierName = value;
    }
    else if (!_strnicmp(key, "CarrierAddress", strlen("CarrierAddress")))
    {
        ASSERT(key[strlen("CarrierAddress")] == '_');
        int i = atoi(&key[strlen("CarrierAddress") + 1]) - 1;
        m_fileContent.vehicles[i].CarrierAddress = value;
    }
    else if (!_strnicmp(key, "CarrierZip", strlen("CarrierZip")))
    {
        ASSERT(key[strlen("CarrierZip")] == '_');
        int i = atoi(&key[strlen("CarrierZip") + 1]) - 1;
        m_fileContent.vehicles[i].CarrierZip = atoi(value);
    }
    else if (!_strnicmp(key, "OwnersName", strlen("OwnersName")))
    {
        ASSERT(key[strlen("OwnersName")] == '_');
        int i = atoi(&key[strlen("OwnersName") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.OwnersFirstName = value;
    }
    else if (!_strnicmp(key, "OwnersCompany", strlen("OwnersCompany")))
    {
        ASSERT(key[strlen("OwnersCompany")] == '_');
        int i = atoi(&key[strlen("OwnersCompany") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.OwnersCompany = value;
    }
    else if (!_strnicmp(key, "OwnersAddress", strlen("OwnersAddress")))
    {
        ASSERT(key[strlen("OwnersAddress")] == '_');
        int i = atoi(&key[strlen("OwnersAddress") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.OwnersAddress = value;
    }
    else if (!_strnicmp(key, "OwnersZip", strlen("OwnersZip")))
    {
        ASSERT(key[strlen("OwnersZip")] == '_');
        int i = atoi(&key[strlen("OwnersZip") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.OwnersZip = atoi(value);
    }
    else if (!_strnicmp(key, "OWNERSPHONE", strlen("OWNERSPHONE")))
    {
        ASSERT(key[strlen("OWNERSPHONE")] == '_');
        int i = atoi(&key[strlen("OWNERSPHONE") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.OWNERSPHONE = value;
    }
    else if (!_strnicmp(key, "InsuredBy", strlen("InsuredBy")))
    {
        ASSERT(key[strlen("InsuredBy")] == '_');
        int i = atoi(&key[strlen("InsuredBy") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.InsuredBy = value;
    }
    else if (!_strnicmp(key, "PolicyNumber", strlen("PolicyNumber")))
    {
        ASSERT(key[strlen("PolicyNumber")] == '_');
        int i = atoi(&key[strlen("PolicyNumber") + 1]) - 1;
        m_fileContent.vehicles[i].Owner.PolicyNumber = value;
    }
    else if (!_strnicmp(key, "Trailer", strlen("Trailer")))
    {
        int i = key[strlen(key) - 1] - '0';
        int j = key[strlen("Trailer")] - '0';
        if (!_strnicmp(&key[strlen("Trailer?")], "Type", strlen("Type")))
        {
            m_fileContent.vehicles[i].Trailer[j].Type = value;
        }
        else if (!_strnicmp(&key[strlen("Trailer?")], "Year", strlen("Year")))
        {
            m_fileContent.vehicles[i].Trailer[j].Year = value;
        }
        else if (!_strnicmp(&key[strlen("Trailer?")], "Make", strlen("Make")))
        {
            m_fileContent.vehicles[i].Trailer[j].Make = value;
        }
        else if (!_strnicmp(&key[strlen("Trailer?")], "LicYear", strlen("LicYear")))
        {
            m_fileContent.vehicles[i].Trailer[j].LicYear = value;
        }
        else if (!_strnicmp(&key[strlen("Trailer?")], "LicState", strlen("LicState")))
        {
            m_fileContent.vehicles[i].Trailer[j].LicState = value;
        }
        else if (!_strnicmp(&key[strlen("Trailer?")], "LicNumber", strlen("LicNumber")))
        {
            m_fileContent.vehicles[i].Trailer[j].LicNumber = value;
        }
        else
        {
            ASSERT(0);
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillConditions(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillConditions(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillConditions(const char* key, const char* value)
{
    if (!_strnicmp(key, "RoadConditionsVe", strlen("RoadConditionsVe")))
    {
        ASSERT(key[strlen("RoadConditionsVe")] == '_');
        int i = atoi(&key[strlen("RoadConditionsVe") + 1]) - 1;
        m_fileContent.conditions[i].RoadConditionsVe = value;
    }
    else if (!_strnicmp(key, "RoadSurfaceVe", strlen("RoadSurfaceVe")))
    {
        ASSERT(key[strlen("RoadSurfaceVe")] == '_');
        int i = atoi(&key[strlen("RoadSurfaceVe") + 1]) - 1;
        m_fileContent.conditions[i].RoadSurfaceVe = value;
    }
    else if (!_strnicmp(key, "TrafficControlDevice", strlen("TrafficControlDevice")))
    {
        ASSERT(key[strlen("TrafficControlDevice")] == '_');
        int i = atoi(&key[strlen("TrafficControlDevice") + 1]) - 1;
        m_fileContent.conditions[i].TrafficControlDevice = value;
    }
    else if (!_strnicmp(key, "RoadDesignLanes", strlen("RoadDesignLanes")))
    {
        ASSERT(key[strlen("RoadDesignLanes")] == '_');
        int i = atoi(&key[strlen("RoadDesignLanes") + 1]) - 1;
        m_fileContent.conditions[i].RoadDesignLanes = value;
    }
    else if (!_strnicmp(key, "RoadDesignDivider", strlen("RoadDesignDivider")))
    {
        ASSERT(key[strlen("RoadDesignDivider")] == '_');
        int i = atoi(&key[strlen("RoadDesignDivider") + 1]) - 1;
        m_fileContent.conditions[i].RoadDesignDivider = value;
    }
    else if (!_strnicmp(key, "RoadDesign", strlen("RoadDesign")))
    {
        ASSERT(key[strlen("RoadDesign")] == '_');
        int i = atoi(&key[strlen("RoadDesign") + 1]) - 1;
        m_fileContent.conditions[i].RoadDesign = value;
    }
    else if (!_strnicmp(key, "ACFAvoidNoContactOther", strlen("ACFAvoidNoContactOther")))
    {
        ASSERT(key[strlen("ACFAvoidNoContactOther")] == '_');
        int i = atoi(&key[strlen("ACFAvoidNoContactOther") + 1]) - 1;
        m_fileContent.conditions[i].ACFAvoidNoContactOther = atoi(value);
    }
    else if (!_strnicmp(key, "ACFAvoidNoContactVe", strlen("ACFAvoidNoContactVe")))
    {
        ASSERT(key[strlen("ACFAvoidNoContactVe")] == '_');
        int i = atoi(&key[strlen("ACFAvoidNoContactVe") + 1]) - 1;
        m_fileContent.conditions[i].ACFAvoidNoContactVe = atoi(value);
    }
    else if (!_strnicmp(key, "ACFCellPhone", strlen("ACFCellPhone")))
    {
        ASSERT(key[strlen("ACFCellPhone")] == '_');
        int i = atoi(&key[strlen("ACFCellPhone") + 1]) - 1;
        m_fileContent.conditions[i].ACFCellPhone = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDefectiveSteering", strlen("ACFDefectiveSteering")))
    {
        ASSERT(key[strlen("ACFDefectiveSteering")] == '_');
        int i = atoi(&key[strlen("ACFDefectiveSteering") + 1]) - 1;
        m_fileContent.conditions[i].ACFDefectiveSteering = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDefectiveTires", strlen("ACFDefectiveTires")))
    {
        ASSERT(key[strlen("ACFDefectiveTires")] == '_');
        int i = atoi(&key[strlen("ACFDefectiveTires") + 1]) - 1;
        m_fileContent.conditions[i].ACFDefectiveTires = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDisregardedTrafficSignal", strlen("ACFDisregardedTrafficSignal")))
    {
        ASSERT(key[strlen("ACFDisregardedTrafficSignal")] == '_');
        int i = atoi(&key[strlen("ACFDisregardedTrafficSignal") + 1]) - 1;
        m_fileContent.conditions[i].ACFDisregardedTrafficSignal = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDriverInattention", strlen("ACFDriverInattention")))
    {
        ASSERT(key[strlen("ACFDriverInattention")] == '_');
        int i = atoi(&key[strlen("ACFDriverInattention") + 1]) - 1;
        m_fileContent.conditions[i].ACFDriverInattention = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDriverlessMovingVe", strlen("ACFDriverlessMovingVe")))
    {
        ASSERT(key[strlen("ACFDriverlessMovingVe")] == '_');
        int i = atoi(&key[strlen("ACFDriverlessMovingVe") + 1]) - 1;
        m_fileContent.conditions[i].ACFDriverlessMovingVe = atoi(value);
    }
    else if (!_strnicmp(key, "ACFDroveLeftOfCenter", strlen("ACFDroveLeftOfCenter")))
    {
        ASSERT(key[strlen("ACFDroveLeftOfCenter")] == '_');
        int i = atoi(&key[strlen("ACFDroveLeftOfCenter") + 1]) - 1;
        m_fileContent.conditions[i].ACFDroveLeftOfCenter = atoi(value);
    }
    else if (!_strnicmp(key, "ACFExcessiveSpeed", strlen("ACFExcessiveSpeed")))
    {
        ASSERT(key[strlen("ACFExcessiveSpeed")] == '_');
        int i = atoi(&key[strlen("ACFExcessiveSpeed") + 1]) - 1;
        m_fileContent.conditions[i].ACFExcessiveSpeed = atoi(value);
    }
    else if (!_strnicmp(key, "ACFFailedToYieldEmgcyVe", strlen("ACFFailedToYieldEmgcyVe")))
    {
        ASSERT(key[strlen("ACFFailedToYieldEmgcyVe")] == '_');
        int i = atoi(&key[strlen("ACFAvoidNoContactVe") + 1]) - 1;
        m_fileContent.conditions[i].ACFFailedToYieldEmgcyVe = atoi(value);
    }
    else if (!_strnicmp(key, "ACFFailedToYieldPoliceVe", strlen("ACFFailedToYieldPoliceVe")))
    {
        ASSERT(key[strlen("ACFFailedToYieldPoliceVe")] == '_');
        int i = atoi(&key[strlen("ACFFailedToYieldPoliceVe") + 1]) - 1;
        m_fileContent.conditions[i].ACFFailedToYieldPoliceVe = atoi(value);
    }
    else if (!_strnicmp(key, "ACFFailedToYieldRightOfWay", strlen("ACFFailedToYieldRightOfWay")))
    {
        ASSERT(key[strlen("ACFFailedToYieldRightOfWay")] == '_');
        int i = atoi(&key[strlen("ACFFailedToYieldRightOfWay") + 1]) - 1;
        m_fileContent.conditions[i].ACFFailedToYieldRightOfWay = atoi(value);
    }
    else if (!_strnicmp(key, "ACFHighSpeedPursuit", strlen("ACFHighSpeedPursuit")))
    {
        ASSERT(key[strlen("ACFHighSpeedPursuit")] == '_');
        int i = atoi(&key[strlen("ACFHighSpeedPursuit") + 1]) - 1;
        m_fileContent.conditions[i].ACFHighSpeedPursuit = atoi(value);
    }
    else if (!_strnicmp(key, "ACFImproperBacking", strlen("ACFImproperBacking")))
    {
        ASSERT(key[strlen("ACFImproperBacking")] == '_');
        int i = atoi(&key[strlen("ACFImproperBacking") + 1]) - 1;
        m_fileContent.conditions[i].ACFImproperBacking = atoi(value);
    }
    else if (!_strnicmp(key, "ACFImproperLaneChange", strlen("ACFImproperLaneChange")))
    {
        ASSERT(key[strlen("ACFImproperLaneChange")] == '_');
        int i = atoi(&key[strlen("ACFImproperLaneChange") + 1]) - 1;
        m_fileContent.conditions[i].ACFImproperLaneChange = atoi(value);
    }
    else if (!_strnicmp(key, "ACFImproperOvertaking", strlen("ACFImproperOvertaking")))
    {
        ASSERT(key[strlen("ACFImproperOvertaking")] == '_');
        int i = atoi(&key[strlen("ACFImproperOvertaking") + 1]) - 1;
        m_fileContent.conditions[i].ACFImproperOvertaking = atoi(value);
    }
    else if (!_strnicmp(key, "ACFInadequateBrakes", strlen("ACFInadequateBrakes")))
    {
        ASSERT(key[strlen("ACFInadequateBrakes")] == '_');
        int i = atoi(&key[strlen("ACFInadequateBrakes") + 1]) - 1;
        m_fileContent.conditions[i].ACFInadequateBrakes = atoi(value);
    }
    else if (!_strnicmp(key, "ACFLowVisibilityDueToSmoke", strlen("ACFLowVisibilityDueToSmoke")))
    {
        ASSERT(key[strlen("ACFLowVisibilityDueToSmoke")] == '_');
        int i = atoi(&key[strlen("ACFLowVisibilityDueToSmoke") + 1]) - 1;
        m_fileContent.conditions[i].ACFLowVisibilityDueToSmoke = atoi(value);
    }
    else if (!_strnicmp(key, "ACFMadeImproperTurn", strlen("ACFMadeImproperTurn")))
    {
        ASSERT(key[strlen("ACFMadeImproperTurn")] == '_');
        int i = atoi(&key[strlen("ACFMadeImproperTurn") + 1]) - 1;
        m_fileContent.conditions[i].ACFMadeImproperTurn = atoi(value);
    }
    else if (!_strnicmp(key, "ACFNone", strlen("ACFNone")))
    {
        ASSERT(key[strlen("ACFNone")] == '_');
        int i = atoi(&key[strlen("ACFNone") + 1]) - 1;
        m_fileContent.conditions[i].ACFNone = atoi(value);
    }
    else if (!_strnicmp(key, "ACFOtherImproperDriving", strlen("ACFOtherImproperDriving")))
    {
        ASSERT(key[strlen("ACFOtherImproperDriving")] == '_');
        int i = atoi(&key[strlen("ACFOtherImproperDriving") + 1]) - 1;
        m_fileContent.conditions[i].ACFOtherImproperDriving = atoi(value);
    }
    else if (!_strnicmp(key, "ACFOtherMechanicalDefect", strlen("ACFOtherMechanicalDefect")))
    {
        ASSERT(key[strlen("ACFOtherMechanicalDefect")] == '_');
        int i = atoi(&key[strlen("ACFOtherMechanicalDefect") + 1]) - 1;
        m_fileContent.conditions[i].ACFOtherMechanicalDefect = atoi(value);
    }
    else if (!_strnicmp(key, "ACFOtherNoDriverError", strlen("ACFOtherNoDriverError")))
    {
        ASSERT(key[strlen("ACFOtherNoDriverError")] == '_');
        int i = atoi(&key[strlen("ACFOtherNoDriverError") + 1]) - 1;
        m_fileContent.conditions[i].ACFOtherNoDriverError = atoi(value);
    }
    else if (!_strnicmp(key, "ACFPassedStopSign", strlen("ACFPassedStopSign")))
    {
        ASSERT(key[strlen("ACFPassedStopSign")] == '_');
        int i = atoi(&key[strlen("ACFPassedStopSign") + 1]) - 1;
        m_fileContent.conditions[i].ACFPassedStopSign = atoi(value);
    }
    else if (!_strnicmp(key, "ACFPedestrianError", strlen("ACFPedestrianError")))
    {
        ASSERT(key[strlen("ACFPedestrianError")] == '_');
        int i = atoi(&key[strlen("ACFPedestrianError") + 1]) - 1;
        m_fileContent.conditions[i].ACFPedestrianError = atoi(value);
    }
    else if (!_strnicmp(key, "ACFRoadDefect", strlen("ACFRoadDefect")))
    {
        ASSERT(key[strlen("ACFRoadDefect")] == '_');
        int i = atoi(&key[strlen("ACFRoadDefect") + 1]) - 1;
        m_fileContent.conditions[i].ACFRoadDefect = atoi(value);
    }
    else if (!_strnicmp(key, "ACFSpeed2FastForConditions", strlen("ACFSpeed2FastForConditions")))
    {
        ASSERT(key[strlen("ACFSpeed2FastForConditions")] == '_');
        int i = atoi(&key[strlen("ACFSpeed2FastForConditions") + 1]) - 1;
        m_fileContent.conditions[i].ACFSpeed2FastForConditions = atoi(value);
    }
    else if (!_strnicmp(key, "ACFTexting", strlen("ACFTexting")))
    {
        ASSERT(key[strlen("ACFTexting")] == '_');
        int i = atoi(&key[strlen("ACFTexting") + 1]) - 1;
        m_fileContent.conditions[i].ACFTexting = atoi(value);
    }
    else if (!_strnicmp(key, "ACFTrafficControlInopMissing", strlen("ACFTrafficControlInopMissing")))
    {
        ASSERT(key[strlen("ACFTrafficControlInopMissing")] == '_');
        int i = atoi(&key[strlen("ACFTrafficControlInopMissing") + 1]) - 1;
        m_fileContent.conditions[i].ACFTrafficControlInopMissing = atoi(value);
    }
    else if (!_strnicmp(key, "ACFUnderInflOfDrugs", strlen("ACFUnderInflOfDrugs")))
    {
        ASSERT(key[strlen("ACFUnderInflOfDrugs")] == '_');
        int i = atoi(&key[strlen("ACFUnderInflOfDrugs") + 1]) - 1;
        m_fileContent.conditions[i].ACFUnderInflOfDrugs = atoi(value);
    }
    else if (!_strnicmp(key, "ACFUnderInfluenceOfAlcohol", strlen("ACFUnderInfluenceOfAlcohol")))
    {
        ASSERT(key[strlen("ACFUnderInfluenceOfAlcohol")] == '_');
        int i = atoi(&key[strlen("ACFUnderInfluenceOfAlcohol") + 1]) - 1;
        m_fileContent.conditions[i].ACFUnderInfluenceOfAlcohol = atoi(value);
    }
    else if (!_strnicmp(key, "ACFVeSkiddedBeforeBrk", strlen("ACFVeSkiddedBeforeBrk")))
    {
        ASSERT(key[strlen("ACFVeSkiddedBeforeBrk")] == '_');
        int i = atoi(&key[strlen("ACFVeSkiddedBeforeBrk") + 1]) - 1;
        m_fileContent.conditions[i].ACFVeSkiddedBeforeBrk = atoi(value);
    }
    else if (!_strnicmp(key, "DABacking", strlen("DABacking")))
    {
        ASSERT(key[strlen("DABacking")] == '_');
        int i = atoi(&key[strlen("DABacking") + 1]) - 1;
        m_fileContent.conditions[i].DABacking = atoi(value);
    }
    else if (!_strnicmp(key, "DAGoingStraight", strlen("DAGoingStraight")))
    {
        ASSERT(key[strlen("DAGoingStraight")] == '_');
        int i = atoi(&key[strlen("DAGoingStraight") + 1]) - 1;
        m_fileContent.conditions[i].DAGoingStraight = atoi(value);
    }
    else if (!_strnicmp(key, "DALeftTurn", strlen("DALeftTurn")))
    {
        ASSERT(key[strlen("DALeftTurn")] == '_');
        int i = atoi(&key[strlen("DALeftTurn") + 1]) - 1;
        m_fileContent.conditions[i].DALeftTurn = atoi(value);
    }
    else if (!_strnicmp(key, "DAOther", strlen("DAOther")))
    {
        ASSERT(key[strlen("DAOther")] == '_');
        int i = atoi(&key[strlen("DAOther") + 1]) - 1;
        m_fileContent.conditions[i].DAOther = atoi(value);
    }
    else if (!_strnicmp(key, "DAOvertakingPassing", strlen("DAOvertakingPassing")))
    {
        ASSERT(key[strlen("DAOvertakingPassing")] == '_');
        int i = atoi(&key[strlen("DAOvertakingPassing") + 1]) - 1;
        m_fileContent.conditions[i].DAOvertakingPassing = atoi(value);
    }
    else if (!_strnicmp(key, "DAParked", strlen("DAParked")))
    {
        ASSERT(key[strlen("DAParked")] == '_');
        int i = atoi(&key[strlen("DAParked") + 1]) - 1;
        m_fileContent.conditions[i].DAParked = atoi(value);
    }
    else if (!_strnicmp(key, "DARightTurn", strlen("DARightTurn")))
    {
        ASSERT(key[strlen("DARightTurn")] == '_');
        int i = atoi(&key[strlen("DARightTurn") + 1]) - 1;
        m_fileContent.conditions[i].DARightTurn = atoi(value);
    }
    else if (!_strnicmp(key, "DASlowing", strlen("DASlowing")))
    {
        ASSERT(key[strlen("DASlowing")] == '_');
        int i = atoi(&key[strlen("DASlowing") + 1]) - 1;
        m_fileContent.conditions[i].DASlowing = atoi(value);
    }
    else if (!_strnicmp(key, "DAStartFromPark", strlen("DAStartFromPark")))
    {
        ASSERT(key[strlen("DAStartFromPark")] == '_');
        int i = atoi(&key[strlen("DAStartFromPark") + 1]) - 1;
        m_fileContent.conditions[i].DAStartFromPark = atoi(value);
    }
    else if (!_strnicmp(key, "DAStartInTrafficLane", strlen("DAStartInTrafficLane")))
    {
        ASSERT(key[strlen("DAStartInTrafficLane")] == '_');
        int i = atoi(&key[strlen("DAStartInTrafficLane") + 1]) - 1;
        m_fileContent.conditions[i].DAStartInTrafficLane = atoi(value);
    }
    else if (!_strnicmp(key, "DAStoppedForSignsSignal", strlen("DAStoppedForSignsSignal")))
    {
        ASSERT(key[strlen("DAStoppedForSignsSignal")] == '_');
        int i = atoi(&key[strlen("DAStoppedForSignsSignal") + 1]) - 1;
        m_fileContent.conditions[i].DAStoppedForSignsSignal = atoi(value);
    }
    else if (!_strnicmp(key, "DAStoppedForTraffic", strlen("DAStoppedForTraffic")))
    {
        ASSERT(key[strlen("DAStoppedForTraffic")] == '_');
        int i = atoi(&key[strlen("DAStoppedForTraffic") + 1]) - 1;
        m_fileContent.conditions[i].DAStoppedForTraffic = atoi(value);
    }
    else if (!_strnicmp(key, "DAUnknown", strlen("DAUnknown")))
    {
        ASSERT(key[strlen("DAUnknown")] == '_');
        int i = atoi(&key[strlen("DAUnknown") + 1]) - 1;
        m_fileContent.conditions[i].DAUnknown = atoi(value);
    }
    else if (!_strnicmp(key, "DAUturn", strlen("DAUturn")))
    {
        ASSERT(key[strlen("DAUturn")] == '_');
        int i = atoi(&key[strlen("DAUturn") + 1]) - 1;
        m_fileContent.conditions[i].DAUturn = atoi(value);
    }
    else if (!_strnicmp(key, "SequenceEvent1", strlen("SequenceEvent1")))
    {
        ASSERT(key[strlen("SequenceEvent1")] == '_');
        int i = atoi(&key[strlen("SequenceEvent1") + 1]) - 1;
        m_fileContent.conditions[i].SequenceEvent1 = atoi(value);
    }
    else if (!_strnicmp(key, "SequenceEvent2", strlen("SequenceEvent2")))
    {
        ASSERT(key[strlen("SequenceEvent2")] == '_');
        int i = atoi(&key[strlen("SequenceEvent2") + 1]) - 1;
        m_fileContent.conditions[i].SequenceEvent2 = atoi(value);
    }
    else if (!_strnicmp(key, "SequenceEvent3", strlen("SequenceEvent3")))
    {
        ASSERT(key[strlen("SequenceEvent3")] == '_');
        int i = atoi(&key[strlen("SequenceEvent3") + 1]) - 1;
        m_fileContent.conditions[i].SequenceEvent3 = atoi(value);
    }
    else if (!_strnicmp(key, "SequenceEvent4", strlen("SequenceEvent4")))
    {
        ASSERT(key[strlen("SequenceEvent4")] == '_');
        int i = atoi(&key[strlen("SequenceEvent4") + 1]) - 1;
        m_fileContent.conditions[i].SequenceEvent4 = atoi(value);
    }
    else if (!_strnicmp(key, "PedAtIntAgainstSignal", strlen("PedAtIntAgainstSignal")))
    {
        ASSERT(key[strlen("PedAtIntAgainstSignal")] == '_');
        int i = atoi(&key[strlen("PedAtIntAgainstSignal") + 1]) - 1;
        m_fileContent.conditions[i].PedAtIntAgainstSignal = atoi(value);
    }
    else if (!_strnicmp(key, "PedAtIntDiagonal", strlen("PedAtIntDiagonal")))
    {
        ASSERT(key[strlen("PedAtIntDiagonal")] == '_');
        int i = atoi(&key[strlen("PedAtIntDiagonal") + 1]) - 1;
        m_fileContent.conditions[i].PedAtIntDiagonal = atoi(value);
    }
    else if (!_strnicmp(key, "PedAtIntNoSignal", strlen("PedAtIntNoSignal")))
    {
        ASSERT(key[strlen("PedAtIntNoSignal")] == '_');
        int i = atoi(&key[strlen("PedAtIntNoSignal") + 1]) - 1;
        m_fileContent.conditions[i].PedAtIntNoSignal = atoi(value);
    }
    else if (!_strnicmp(key, "PedAtIntWithSignal", strlen("PedAtIntWithSignal")))
    {
        ASSERT(key[strlen("PedAtIntWithSignal")] == '_');
        int i = atoi(&key[strlen("PedAtIntWithSignal") + 1]) - 1;
        m_fileContent.conditions[i].PedAtIntWithSignal = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntCrosswalk", strlen("PedNotIntCrosswalk")))
    {
        ASSERT(key[strlen("PedNotIntCrosswalk")] == '_');
        int i = atoi(&key[strlen("PedNotIntCrosswalk") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntCrosswalk = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntFromBehindObstruct", strlen("PedNotIntFromBehindObstruct")))
    {
        ASSERT(key[strlen("PedNotIntFromBehindObstruct")] == '_');
        int i = atoi(&key[strlen("PedNotIntFromBehindObstruct") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntFromBehindObstruct = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntNoCrosswalk", strlen("PedNotIntNoCrosswalk")))
    {
        ASSERT(key[strlen("PedNotIntNoCrosswalk")] == '_');
        int i = atoi(&key[strlen("PedNotIntNoCrosswalk") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntNoCrosswalk = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntOther", strlen("PedNotIntOther")))
    {
        ASSERT(key[strlen("PedNotIntOther")] == '_');
        int i = atoi(&key[strlen("PedNotIntOther") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntOther = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntPlayinginRoad", strlen("PedNotIntPlayinginRoad")))
    {
        ASSERT(key[strlen("PedNotIntPlayinginRoad")] == '_');
        int i = atoi(&key[strlen("PedNotIntPlayinginRoad") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntPlayinginRoad = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntPushWorkOnVe", strlen("PedNotIntPushWorkOnVe")))
    {
        ASSERT(key[strlen("PedNotIntPushWorkOnVe")] == '_');
        int i = atoi(&key[strlen("PedNotIntPushWorkOnVe") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntPushWorkOnVe = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntStanding", strlen("PedNotIntStanding")))
    {
        ASSERT(key[strlen("PedNotIntStanding")] == '_');
        int i = atoi(&key[strlen("PedNotIntStanding") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntStanding = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntWalkAgainstTraffic", strlen("PedNotIntWalkAgainstTraffic")))
    {
        ASSERT(key[strlen("PedNotIntWalkAgainstTraffic")] == '_');
        int i = atoi(&key[strlen("PedNotIntWalkAgainstTraffic") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntWalkAgainstTraffic = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntWalkWithTraffic", strlen("PedNotIntWalkWithTraffic")))
    {
        ASSERT(key[strlen("PedNotIntWalkWithTraffic")] == '_');
        int i = atoi(&key[strlen("PedNotIntWalkWithTraffic") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntWalkWithTraffic = atoi(value);
    }
    else if (!_strnicmp(key, "PedNotIntOtherText", strlen("PedNotIntOtherText")))
    {
        ASSERT(key[strlen("PedNotIntOtherText")] == '_');
        int i = atoi(&key[strlen("PedNotIntOtherText") + 1]) - 1;
        m_fileContent.conditions[i].PedNotIntOtherText = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionAmputee", strlen("ConditionAmputee")))
    {
        ASSERT(key[strlen("ConditionAmputee")] == '_');
        int i = atoi(&key[strlen("ConditionAmputee") + 1]) - 1;
        m_fileContent.conditions[i].ConditionAmputee = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionEyesightImpaired", strlen("ConditionEyesightImpaired")))
    {
        ASSERT(key[strlen("ConditionEyesightImpaired")] == '_');
        int i = atoi(&key[strlen("ConditionEyesightImpaired") + 1]) - 1;
        m_fileContent.conditions[i].ConditionEyesightImpaired = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionFatiguedAsleep", strlen("ConditionFatiguedAsleep")))
    {
        ASSERT(key[strlen("ConditionFatiguedAsleep")] == '_');
        int i = atoi(&key[strlen("ConditionFatiguedAsleep") + 1]) - 1;
        m_fileContent.conditions[i].ConditionFatiguedAsleep = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionHearingImpaired", strlen("ConditionHearingImpaired")))
    {
        ASSERT(key[strlen("ConditionHearingImpaired")] == '_');
        int i = atoi(&key[strlen("ConditionHearingImpaired") + 1]) - 1;
        m_fileContent.conditions[i].ConditionHearingImpaired = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionIllness", strlen("ConditionIllness")))
    {
        ASSERT(key[strlen("ConditionIllness")] == '_');
        int i = atoi(&key[strlen("ConditionIllness") + 1]) - 1;
        m_fileContent.conditions[i].ConditionIllness = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionMedsDrugsAlcohol", strlen("ConditionMedsDrugsAlcohol")))
    {
        ASSERT(key[strlen("ConditionMedsDrugsAlcohol")] == '_');
        int i = atoi(&key[strlen("ConditionMedsDrugsAlcohol") + 1]) - 1;
        m_fileContent.conditions[i].ConditionMedsDrugsAlcohol = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionNoAppDefects", strlen("ConditionNoAppDefects")))
    {
        ASSERT(key[strlen("ConditionNoAppDefects")] == '_');
        int i = atoi(&key[strlen("ConditionNoAppDefects") + 1]) - 1;
        m_fileContent.conditions[i].ConditionNoAppDefects = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionOther", strlen("ConditionOther")))
    {
        ASSERT(key[strlen("ConditionOther")] == '_');
        int i = atoi(&key[strlen("ConditionOther") + 1]) - 1;
        m_fileContent.conditions[i].ConditionOther = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionUnknown", strlen("ConditionUnknown")))
    {
        ASSERT(key[strlen("ConditionUnknown")] == '_');
        int i = atoi(&key[strlen("ConditionUnknown") + 1]) - 1;
        m_fileContent.conditions[i].ConditionUnknown = atoi(value);
    }
    else if (!_strnicmp(key, "ConditionOtherText", strlen("ConditionOtherText")))
    {
        ASSERT(key[strlen("ConditionOtherText")] == '_');
        int i = atoi(&key[strlen("ConditionOtherText") + 1]) - 1;
        m_fileContent.conditions[i].ConditionOtherText = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyBAC", strlen("SobrietyBAC")))
    {
        ASSERT(key[strlen("SobrietyBAC")] == '_');
        int i = atoi(&key[strlen("SobrietyBAC") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyBAC = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyBloodTest", strlen("SobrietyBloodTest")))
    {
        ASSERT(key[strlen("SobrietyBloodTest")] == '_');
        int i = atoi(&key[strlen("SobrietyBloodTest") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyBloodTest = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyConsumeAlcohol", strlen("SobrietyConsumeAlcohol")))
    {
        ASSERT(key[strlen("SobrietyConsumeAlcohol")] == '_');
        int i = atoi(&key[strlen("SobrietyConsumeAlcohol") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyConsumeAlcohol = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyConsumeCtrlSubtance", strlen("SobrietyConsumeCtrlSubtance")))
    {
        ASSERT(key[strlen("SobrietyConsumeCtrlSubtance")] == '_');
        int i = atoi(&key[strlen("SobrietyConsumeCtrlSubtance") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyConsumeCtrlSubtance = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyConsumeMeds", strlen("SobrietyConsumeMeds")))
    {
        ASSERT(key[strlen("SobrietyConsumeMeds")] == '_');
        int i = atoi(&key[strlen("SobrietyConsumeMeds") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyConsumeMeds = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyFieldSobrietyTest", strlen("SobrietyFieldSobrietyTest")))
    {
        ASSERT(key[strlen("SobrietyFieldSobrietyTest")] == '_');
        int i = atoi(&key[strlen("SobrietyFieldSobrietyTest") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyFieldSobrietyTest = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyNotConsumeAlcohol", strlen("SobrietyNotConsumeAlcohol")))
    {
        ASSERT(key[strlen("SobrietyNotConsumeAlcohol")] == '_');
        int i = atoi(&key[strlen("SobrietyNotConsumeAlcohol") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyNotConsumeAlcohol = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyTestByInst", strlen("SobrietyTestByInst")))
    {
        ASSERT(key[strlen("SobrietyTestByInst")] == '_');
        int i = atoi(&key[strlen("SobrietyTestByInst") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyTestByInst = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyTestRefused", strlen("SobrietyTestRefused")))
    {
        ASSERT(key[strlen("SobrietyTestRefused")] == '_');
        int i = atoi(&key[strlen("SobrietyTestRefused") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyTestRefused = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyUnknown", strlen("SobrietyUnknown")))
    {
        ASSERT(key[strlen("SobrietyUnknown")] == '_');
        int i = atoi(&key[strlen("SobrietyUnknown") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyUnknown = atoi(value);
    }
    else if (!_strnicmp(key, "SobrietyBreathTest", strlen("SobrietyBreathTest")))
    {
        ASSERT(key[strlen("SobrietyBreathTest")] == '_');
        int i = atoi(&key[strlen("SobrietyBreathTest") + 1]) - 1;
        m_fileContent.conditions[i].SobrietyBreathTest = atoi(value);
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillNarrative(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillNarrative(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillNarrative(const char* key, const char* value)
{
    if (!_stricmp(key, "Narrative"))
    {
        m_fileContent.narrative.Narrative = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillProperties(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillProperties(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillProperties(const char* key, const char* value)
{
    if (!_strnicmp(key, "pType", strlen("pType")))
    {
        ASSERT(key[strlen("pType")] == '_');
        int i = atoi(&key[strlen("pType") + 1]) - 1;
        m_fileContent.properties[i].pType = value;
    }
    else if (!_strnicmp(key, "pDesc", strlen("pDesc")))
    {
        ASSERT(key[strlen("pDesc")] == '_');
        int i = atoi(&key[strlen("pDesc") + 1]) - 1;
        m_fileContent.properties[i].pDesc = value;
    }
    else if (!_strnicmp(key, "pLastName", strlen("pLastName")))
    {
        ASSERT(key[strlen("pLastName")] == '_');
        int i = atoi(&key[strlen("pLastName") + 1]) - 1;
        m_fileContent.properties[i].pLastName = value;
    }
    else if (!_strnicmp(key, "pFirstName", strlen("pFirstName")))
    {
        ASSERT(key[strlen("pFirstName")] == '_');
        int i = atoi(&key[strlen("pFirstName") + 1]) - 1;
        m_fileContent.properties[i].pFirstName = value;
    }
    else if (!_strnicmp(key, "pMiddleName", strlen("pMiddleName")))
    {
        ASSERT(key[strlen("pMiddleName")] == '_');
        int i = atoi(&key[strlen("pMiddleName") + 1]) - 1;
        m_fileContent.properties[i].pMiddleName = value;
    }
    else if (!_strnicmp(key, "pAddress", strlen("pAddress")))
    {
        ASSERT(key[strlen("pAddress")] == '_');
        int i = atoi(&key[strlen("pAddress") + 1]) - 1;
        m_fileContent.properties[i].pAddress = value;
    }
    else if (!_strnicmp(key, "pCity", strlen("pCity")))
    {
        ASSERT(key[strlen("pCity")] == '_');
        int i = atoi(&key[strlen("pCity") + 1]) - 1;
        m_fileContent.properties[i].pCity = value;
    }
    else if (!_strnicmp(key, "pState", strlen("pState")))
    {
        ASSERT(key[strlen("pState")] == '_');
        int i = atoi(&key[strlen("pState") + 1]) - 1;
        m_fileContent.properties[i].pState = value;
    }
    else if (!_strnicmp(key, "pZip", strlen("pZip")))
    {
        ASSERT(key[strlen("pZip")] == '_');
        int i = atoi(&key[strlen("pZip") + 1]) - 1;
        m_fileContent.properties[i].pZip = atoi(value);
    }
    else if (!_strnicmp(key, "pPhone", strlen("pPhone")))
    {
        ASSERT(key[strlen("pPhone")] == '_');
        int i = atoi(&key[strlen("pPhone") + 1]) - 1;
        m_fileContent.properties[i].pPhone = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillViolations(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillViolations(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillViolations(const char* key, const char* value)
{
    if (!_stricmp(key, "vLastName"))
    {
        int i = atoi(&key[strlen("vLastName")]) - 1;
        m_fileContent.violations[i].vLastName = value;
    }
    else if (!_stricmp(key, "vFirstName"))
    {
        int i = atoi(&key[strlen("vFirstName")]) - 1;
        m_fileContent.violations[i].vFirstName = value;
    }
    else if (!_stricmp(key, "vMiddleName"))
    {
        int i = atoi(&key[strlen("vMiddleName")]) - 1;
        m_fileContent.violations[i].vMiddleName = value;
    }
    else if (!_stricmp(key, "vAction"))
    {
        int i = atoi(&key[strlen("vAction")]) - 1;
        m_fileContent.violations[i].vAction = value;
    }
    else if (!_stricmp(key, "vViolation"))
    {
        int i = atoi(&key[strlen("vViolation")]) - 1;
        m_fileContent.violations[i].vViolation = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillConclusion(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillConclusion(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillConclusion(const char* key, const char* value)
{
    if (!_stricmp(key, "TimeNotified"))
    {
        m_fileContent.conclusion.TimeNotified = value;
    }
    else if (!_stricmp(key, "TimeArrived"))
    {
        m_fileContent.conclusion.TimeArrived = value;
    }
    else if (!_stricmp(key, "NotifiedBy"))
    {
        m_fileContent.conclusion.NotifiedBy = value;
    }
    else if (!_stricmp(key, "SupervisorOnScene"))
    {
        m_fileContent.conclusion.SupervisorOnScene = value;
    }
    else if (!_stricmp(key, "Checkedby"))
    {
        m_fileContent.conclusion.Checkedby = value;
    }
    else if (!_stricmp(key, "OfficersSignaturePresent"))
    {
        m_fileContent.conclusion.OfficersSignaturePresent = atoi(value);
    }
    else if (!_stricmp(key, "District"))
    {
        m_fileContent.conclusion.District = atoi(value);
    }
    else if (!_stricmp(key, "ReportDate"))
    {
        m_fileContent.conclusion.ReportDate = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillDiagram(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillSummary(key, value);
        }

        child = child->NextSibling();
    }
    return 0;
}

int CDataParser::FillDiagram(const char* key, const char* value)
{
    if (!_stricmp(key, "DrawingsBy"))
    {
        m_fileContent.diagram.DrawingsBy = value;
    }
    else if (!_stricmp(key, "MeasurementsTakenBy"))
    {
        m_fileContent.diagram.MeasurementsTakenBy = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::FillLocation(TiXmlNode* root)
{
    TiXmlNode* child = root->FirstChildElement();
    while (child) {
        const char* key = child->Value();

        const char* value = NULL;
        if (child->FirstChild())
        {
            value = child->FirstChild()->Value();
        }
        else
        {
            value = NULL;
        }
        TRACE("K = %s, V = %s\n", key, value);
        if (value)
        {
            FillLocation(key, value);
        }

        child = child->NextSibling();
    }

    return 0;
}

int CDataParser::FillLocation(const char* key, const char* value)
{
    if (!_stricmp(key, "LiteralDescription"))
    {
        m_fileContent.location.LiteralDescription = value;
    }
    else if (!_stricmp(key, "XCoordinate"))
    {
        m_fileContent.location.XCoordinate = value;
    }
    else if (!_stricmp(key, "YCoordinate"))
    {
        m_fileContent.location.YCoordinate = value;
    }
    else
    {
        return 1;
    }

    return 0;
}

int CDataParser::GetUCRNumber(UINT& ucrNumber)
{
    if (!m_strFileName.IsEmpty())
    {
        ucrNumber = m_fileContent.summary.UCRNumber;
        return 0;
    }

    return 1;
}

int CDataParser::GetSQL_crash(CString& strSql)
{
    strSql.Format(
        _T("INSERT INTO [dbo].[Acrash2012]     ")
        _T("([ucrnumber]                       ")
        _T(",[crashdate]                       ")
        _T(",[militarytime]                    ")
        _T(",[reportdate]                      ")
        _T(",[date_time]                       ")
        _T(",[ucrorig]                         ")
        _T(",[accdateorig]                     ")
        _T(",[agency]                          ")
        _T(",[agencyid]                        ")
        _T(",[analysiscode]                    ")
        _T(",[analysis]                        ")
        _T(",[batchnumber]                     ")
        _T(",[astreet]                         ")
        _T(",[bstreet]                         ")
        _T(",[landmark]                        ")
        _T(",[milepostKofax]                   ")
        _T(",[cadnumber]                       ")
        _T(",[casenumber]                      ")
        _T(",[checkedby]                       ")
        _T(",[city]                            ")
        _T(",[county]                          ")
        _T(",[urbnrurl]                        ")
        _T(",[Classification_Result]           ")
        _T(",[CrashClassification]             ")
        _T(",[CrashOccurrence]                 ")
        _T(",[DirectionFromLandmark]           ")
        _T(",[District]                        ")
        _T(",[Fatal_Injury]                    ")
        _T(",[FormID]                          ")
        _T(",[FormMethod]                      ")
        _T(",[HitRun]                          ")
        _T(",[Latitude]                        ")
        _T(",[Lighting]                        ")
        _T(",[Longitude]                       ")
        _T(",[Measurement]                     ")
        _T(",[MeasurementsTakenBy]             ")
        _T(",[MeasurementUnit]                 ")
        _T(",[NMDOTNumber]                     ")
        _T(",[NotifiedBy]                      ")
        _T(",[NumberofDrawings]                ")
        _T(",[DrawingsBy]                      ")
        _T(",[NumberofVehicles]                ")
        _T(",[OfficerAtScene]                  ")
        _T(",[OfficersSignaturePresent]        ")
        _T(",[PrivateProperty]                 ")
        _T(",[PropertyDamage]                  ")
        _T(",[RoadCharacter]                   ")
        _T(",[RoadGrade]                       ")
        _T(",[StationReport]                   ")
        _T(",[SupervisorOnScene]               ")
        _T(",[TimeArrived]                     ")
        _T(",[TimeNotified]                    ")
        _T(",[TribalJurisdiction]              ")
        _T(",[Weather]                         ")
        _T(",[WeekDay]                         ")
        _T(",[WitnessPresent]                  ")
        _T(",[pDesc]                           ")
        _T(",[pType]                           ")
        _T(",[pAddress]                        ")
        _T(",[pCity]                           ")
        _T(",[pState]                          ")
        _T(",[pZip]                            ")
        _T(",[pPhone]                          ")
        _T(",[pFirstName]                      ")
        _T(",[pLastName]                       ")
        _T(",[pMiddleName]                     ")
        _T(",[FormIDKofax]                     ")
        _T(",[Year]                            ")
        _T(",[Month]                           ")
        _T(",[Hour]                            ")
        _T(",[nVeh]                            ")
        _T(",[Severity]                        ")
        _T(",[System]                          ")
        _T(",[topcfacc]                        ")
        _T(",[Alcinv]                          ")
        _T(",[Druginv]                         ")
        _T(",[MCinv]                           ")
        _T(",[PDinv]                           ")
        _T(",[PCinv]                           ")
        _T(",[TRKinv]                          ")
        _T(",[HZinv]                           ")
        _T(",[MotorVeh]                        ")
        _T(",[Killed]                          ")
        _T(",[Injured]                         ")
        _T(",[ClassA]                          ")
        _T(",[ClassB]                          ")
        _T(",[ClassC]                          ")
        _T(",[Unhurt]                          ")
        _T(",[Total]                           ")
        _T(",[Motorists]                       ")
        _T(",[NonMotorists]                    ")
        _T(",[GIS_Astreet]                     ")
        _T(",[GIS_Bstreet]                     ")
        _T(",[GIS_Location]                    ")
        _T(",[GIS_Route]                       ")
        _T(",[GIS_Milepost]                    ")
        _T(",[GIS_UrbanRural]                  ")
        _T(",[GIS_County]                      ")
        _T(",[GIS_CityE911]                    ")
        _T(",[GIS_CityUSCensus]                ")
        _T(",[GIS_NatAmer_USCensus]            ")
        _T(",[GIS_TransDist]                   ")
        _T(",[GIS_MaintDist]                   ")
        _T(",[GIS_UTM_X]                       ")
        _T(",[GIS_UTM_Y]                       ")
        _T(",[GIS_LAT]                         ")
        _T(",[GIS_LONG]                        ")
        _T(",[source]                          ")
        _T(",[NMDOTID]                         ")
        _T(",[SysBatchNumber]                  ")
        _T(",[SysScanDate])                    ")
        _T("VALUES ")
        
        
        _T("(%d")    //<ucrnumber, float, >
        _T(",'%s'")  //<crashdate, nvarchar(255), >
        _T(",'%s'")  //<militarytime, nvarchar(255), >
        _T(",'%s'")  //<reportdate, nvarchar(255), >
        _T(",'%s'")  //<date_time, nvarchar(255), >
        _T(",'%s'")  //<ucrorig, nvarchar(max), >
        _T(",'%s'")  //<accdateorig, nvarchar(255), >
        _T(",'%s'")  //<agency, nvarchar(max), >
        _T(",'%d'")  //<agencyid, nvarchar(max), >
        _T(",'%s'")  //<analysiscode, nvarchar(max), >
        _T(",'%s'")  //<analysis, nvarchar(max), >
        _T(",'%s'")  //<batchnumber, nvarchar(max), >
        _T(",'%s'")  //<astreet, nvarchar(max), >
        _T(",'%s'")  //<bstreet, nvarchar(max), >
        _T(",'%s'")  //<landmark, nvarchar(max), >
        _T(",'%s'")  //<milepostKofax, nvarchar(max), >
        _T(",'%d'")  //<cadnumber, nvarchar(max), >
        _T(",'%d'")  //<casenumber, nvarchar(max), >
        _T(",'%s'")  //<checkedby, nvarchar(max), >
        _T(",'%s'")  //<city, nvarchar(max), >
        _T(",'%d'")  //<county, nvarchar(max), >
        _T(",'%s'")  //<urbnrurl, nvarchar(max),>
        _T(",'%s'")  //<Classification_Result, nvarchar(m")
        _T(",'%s'")  //<CrashClassification, nvarchar(max")
        _T(",'%s'")  //<CrashOccurrence, nvarchar(max),> ")
        _T(",'%s'")  //<DirectionFromLandmark, nvarchar(m")
        _T(",'%d'")  //<District, nvarchar(max),>        ")
        _T(",'%d'")  //<Fatal_Injury, nvarchar(max),>    ")
        _T(",'%s'")  //<FormID, nvarchar(max),>          ")
        _T(",'%s'")  //<FormMethod, nvarchar(max),>      ")
        _T(",'%d'")  //<HitRun, nvarchar(max),>          ")
        _T(",'%s'")  //<Latitude, nvarchar(max),>        ")
        _T(",'%s'")  //<Lighting, nvarchar(max),>        ")
        _T(",'%s'")  //<Longitude, nvarchar(max),>       ")
        _T(",%d")  //<Measurement, float,>             ")
        _T(",'%s'")  //<MeasurementsTakenBy, nvarchar(max")
        _T(",'%s'")  //<MeasurementUnit, nvarchar(max),> ")
        _T(",'%d'")  //<NMDOTNumber, nvarchar(max),>     ")
        _T(",'%s'")  //<NotifiedBy, nvarchar(max),>      ")
        _T(",'%d'")  //<NumberofDrawings, nvarchar(max),>")
        _T(",'%s'")  //<DrawingsBy, nvarchar(max),>      ")
        _T(",%d")  //<NumberofVehicles, float,>        ")
        _T(",'%s'")  //<OfficerAtScene, nvarchar(max),>  ")
        _T(",'%d'")  //<OfficersSignaturePresent, nvarcha")
        _T(",'%d'")  //<PrivateProperty, nvarchar(max),> ")
        _T(",'%d'")  //<PropertyDamage, nvarchar(max),>  ")
        _T(",'%s'")  //<RoadCharacter, nvarchar(max),>   ")
        _T(",'%s'")  //<RoadGrade, nvarchar(max),>       ")
        _T(",'%s'")  //<StationReport, nvarchar(max),>   ")
        _T(",'%s'")  //<SupervisorOnScene, nvarchar(max),")
        _T(",'%s'")  //<TimeArrived, nvarchar(255),>     ")
        _T(",'%s'")  //<TimeNotified, nvarchar(255),>    ")
        _T(",'%s'")  //<TribalJurisdiction, nvarchar(max)")
        _T(",'%s'")  //<Weather, nvarchar(max),>         ")
        _T(",%d")  //<WeekDay, float,>                 ")
        _T(",'%d'")  //<WitnessPresent, nvarchar(max),>  ")
        _T(",'%s'")  //<pDesc, nvarchar(max),>           ")
        _T(",'%s'")  //<pType, nvarchar(max),>           ")
        _T(",'%s'")  //<pAddress, nvarchar(max),>        ")
        _T(",'%s'")  //<pCity, nvarchar(max),>           ")
        _T(",'%s'")  //<pState, nvarchar(max),>          ")
        _T(",%d")  //<pZip, float,>                    ")
        _T(",'%s'")  //<pPhone, nvarchar(max),>          ")
        _T(",'%s'")  //<pFirstName, nvarchar(max),>      ")
        _T(",'%s'")  //<pLastName, nvarchar(max),>       ")
        _T(",'%s'")  //<pMiddleName, nvarchar(max),>     ")
        _T(",'%s'")  //<FormIDKofax, nvarchar(max),>     ")
        _T(",%d")  //<Year, float,>                    ")
        _T(",%d")  //<Month, float,>                   ")
        _T(",%d")  //<Hour, float,>                    ")
        _T(",%d")  //<nVeh, float,>                    ")
        _T(",%d")  //<Severity, float,>                ")
        _T(",%d")  //<System, float,>                  ")
        _T(",%d")  //<topcfacc, float,>                ")
        _T(",%d")  //<Alcinv, float,>                  ")
        _T(",%d")  //<Druginv, float,>                 ")
        _T(",%d")  //<MCinv, float,>                   ")
        _T(",%d")  //<PDinv, float,>                   ")
        _T(",%d")  //<PCinv, float,>                   ")
        _T(",%d")  //<TRKinv, float,>                  ")
        _T(",%d")  //<HZinv, float,>                   ")
        _T(",%d")  //<MotorVeh, float,>                ")
        _T(",%d")  //<Killed, float,>                  ")
        _T(",%d")  //<Injured, float,>                 ")
        _T(",%d")  //<ClassA, float,>                  ")
        _T(",%d")  //<ClassB, float,>                  ")
        _T(",%d")  //<ClassC, float,>                  ")
        _T(",%d")  //<Unhurt, float,>                  ")
        _T(",%d")  //<Total, float,>                   ")
        _T(",%d")  //<Motorists, float,>               ")
        _T(",%d")  //<NonMotorists, float,>            ")
        _T(",'%s'")  //<GIS_Astreet, nvarchar(max),>     ")
        _T(",'%s'")  //<GIS_Bstreet, nvarchar(max),>     ")
        _T(",'%s'")  //<GIS_Location, nvarchar(max),>    ")
        _T(",'%s'")  //<GIS_Route, nvarchar(max),>       ")
        _T(",'%s'")  //<GIS_Milepost, nvarchar(max),>    ")
        _T(",'%s'")  //<GIS_UrbanRural, nvarchar(max),>  ")
        _T(",'%s'")  //<GIS_County, nvarchar(max),>      ")
        _T(",'%s'")  //<GIS_CityE911, nvarchar(max),>    ")
        _T(",'%s'")  //<GIS_CityUSCensus, nvarchar(max),>")
        _T(",'%s'")  //<GIS_NatAmer_USCensus, nvarchar(ma")
        _T(",%d")  //<GIS_TransDist, float,>           ")
        _T(",%d")  //<GIS_MaintDist, float,>           ")
        _T(",%d")  //<GIS_UTM_X, float,>               ")
        _T(",%d")  //<GIS_UTM_Y, float,>               ")
        _T(",%d")  //<GIS_LAT, float,>                 ")
        _T(",%d")  //<GIS_LONG, float,>                ")
        _T(",%d")  //<source, nvarchar(max),>          ")
        _T(",%d")  //<NMDOTID, float,>                 ")
        _T(",'%s'")  //<SysBatchNumber, nvarchar(max),>  ")
        _T(",'%s')"), //<SysScanDate, nvarchar(255),>)    "), 

        m_fileContent.summary.UCRNumber,
        m_fileContent.summary.CrashDate,
        m_fileContent.summary.MilitaryTime,
        m_fileContent.conclusion.ReportDate,
        _T(""), // date_time
        _T(""), // ucrorig
        _T(""), // accdateorig
        m_fileContent.summary.Agency,
        m_fileContent.Agency,
        m_fileContent.summary.AnalysisCode,
        _T(""), // analysis
        _T(""), // batchnumber
        m_fileContent.summary.STREETA,
        m_fileContent.summary.INTERSECTING_STREETB,
        m_fileContent.summary.Landmark,
        m_fileContent.summary.Milepost,
        m_fileContent.summary.CADNumber,
        m_fileContent.CaseNumber,
        m_fileContent.conclusion.Checkedby,
        m_fileContent.summary.City,
        m_fileContent.summary.County,
        _T(""), // urbnrurl
        _T(""), // Classification_Result
        m_fileContent.summary.CrashClassification,
        m_fileContent.summary.CRASHOCCURRENCE,
        m_fileContent.summary.DirectionFromLandmark,
        m_fileContent.conclusion.District,
        m_fileContent.summary.Fatal_Injury,
        _T(""), // FormID
        _T(""), // FormMethod, 
        m_fileContent.summary.Hit_Run,
        m_fileContent.summary.Landmark,
        m_fileContent.summary.Lighting,
        m_fileContent.summary.Longitude,
        m_fileContent.summary.Measurement,
        m_fileContent.diagram.MeasurementsTakenBy,
        m_fileContent.summary.MeasurementUnit,
        m_fileContent.summary.NMDOTNumber,
        m_fileContent.conclusion.NotifiedBy, 
        m_fileContent.NumberofDrawings, 
        m_fileContent.diagram.DrawingsBy,
        m_fileContent.NumberofVehicles,
        m_fileContent.OfficerAtScene,
        m_fileContent.conclusion.OfficersSignaturePresent,
        m_fileContent.summary.PrivateProperty,
        m_fileContent.PropertyDamage,
        m_fileContent.summary.RoadCharacter,
        m_fileContent.summary.RoadGrade,
        _T(""), // StationReport
        m_fileContent.conclusion.SupervisorOnScene,
        m_fileContent.conclusion.TimeArrived,
        m_fileContent.conclusion.TimeNotified,
        m_fileContent.summary.TribalJurisdiction,
        m_fileContent.summary.WEATHER,
        m_fileContent.summary.WeekDay,
        m_fileContent.WitnessPresent,
        m_fileContent.properties[0].pDesc,
        m_fileContent.properties[0].pType,
        m_fileContent.properties[0].pAddress,
        m_fileContent.properties[0].pCity,
        m_fileContent.properties[0].pState,
        m_fileContent.properties[0].pZip,
        m_fileContent.properties[0].pPhone,
        m_fileContent.properties[0].pFirstName,
        m_fileContent.properties[0].pLastName,
        m_fileContent.properties[0].pMiddleName,
        _T(""), // FormIDKofax
        0,  // year
        0,  // month 
        0,  // hour 
        0,  // nVeh 
        0,  // severity 
        0,  // System
        0,  // topcfacc 
        0,  // alcinv 
        0,  // druginv 
        0,  // mcinv 
        0,  // pdinv 
        0,  // pcinv
        0,  // trkinv
        0,  // hzinv
        0,  // motorveh 
        0,  // killed 
        0,  // injured 
        0,  // classA
        0,  // classB 
        0,  // classC 
        0,  // unhurt
        0,  // total 
        0,  // motorists 
        0,  // nonmotorists
        _T(""), //<GIS_Astreet, nvarcha        );
        _T(""), //<GIS_Bstreet, nvarcha
        _T(""), //<GIS_Location, nvarch    return 0;
        _T(""), //<GIS_Route, nvarchar(}
        _T(""), //<GIS_Milepost, nvarch
        _T(""), //<GIS_UrbanRural, nvarint CDataParser::GetSQL_occupant(CString& strSql)
        _T(""), //<GIS_County, nvarchar{
        _T(""), //<GIS_CityE911, nvarch    return 0;
        _T(""), //<GIS_CityUSCensus, nv}
        _T(""), //<GIS_NatAmer_USCensus
        _T(""), //<GIS_TransDist, float,>int CDataParser::GetSQL_vehicle(CString& strSql)
        _T(""), //<GIS_MaintDist, float,>{
        _T(""), //<GIS_UTM_X, float,>        return 0;
        _T(""), //<GIS_UTM_Y, float,>    }
        _T(""), //<GIS_LAT, float,>      
        _T(""), //<GIS_LONG, float,>     
        _T(""), //<source, nvarchar(max),
        _T(""), //<NMDOTID, float,>      
        _T(""), //<SysBatchNumber, nvar
        _T("") //<SysScanDate, nvarcha
        );

#ifdef DEBUG
    OutputDebugString(strSql.GetString());
#endif

    return 0;
}

int CDataParser::GetSQL_occupant(CString& strSql)
{
    for (UINT i = 0; i < m_fileContent.NumberofVehicles; ++i)
    {
        UINT j = 0;
        while (!m_fileContent.vehicles[i].Occupant[j].oSeatPos.IsEmpty())
        {
            CString strOccupant;
            strOccupant.Format(
                _T("INSERT INTO [dbo].[Aoccupant2012]")
                _T("([UCRVehnoPosFNLNAgeSexCity] ")
                _T(",[ucrnumber]                 ")
                _T(",[crashdate]                 ")
                _T(",[vehno]                     ")
                _T(",[oSeatPos]                  ")
                _T(",[oFirstName]                ")
                _T(",[oLastName]                 ")
                _T(",[oMiddleName]               ")
                _T(",[oAge]                      ")
                _T(",[oSex]                      ")
                _T(",[oRace]                     ")
                _T(",[oInjuryCode]               ")
                _T(",[oOPCode]                   ")
                _T(",[oOPProperlyUsed]           ")
                _T(",[oAirbagDeployed]           ")
                _T(",[oEjected]                  ")
                _T(",[oEMSNum]                   ")
                _T(",[oMedTrans]                 ")
                _T(",[oAddress]                  ")
                _T(",[oCity]                     ")
                _T(",[oState]                    ")
                _T(",[oZip])                     ")
                _T("VALUES")
                _T("('%s'")	    // <UCRVehnoPosFNLNAgeSexCity, nvarchar(max),>
                _T(",%d")	    // <ucrnumber, float,>
                _T(",'%s'")	    // <crashdate, nvarchar(255),>
                _T(",%d")	    // <vehno, float,>
                _T(",'%s'")	    // <oSeatPos, nvarchar(max),>
                _T(",'%s'")	    // <oFirstName, nvarchar(max),>
                _T(",'%s'")	    // <oLastName, nvarchar(max),>
                _T(",'%s'")	    // <oMiddleName, nvarchar(max),>
                _T(",%d")	    // <oAge, float,>
                _T(",'%s'")	    // <oSex, nvarchar(max),>
                _T(",'%s'")	    // <oRace, nvarchar(max),>
                _T(",'%s'")	    // <oInjuryCode, nvarchar(max),>
                _T(",'%s'")	    // <oOPCode, nvarchar(max),>
                _T(",'%s'")	    // <oOPProperlyUsed, nvarchar(max),>
                _T(",'%s'")	    // <oAirbagDeployed, nvarchar(max),>
                _T(",'%s'")	    // <oEjected, nvarchar(max),>
                _T(",'%s'")	    // <oEMSNum, nvarchar(max),>
                _T(",'%s'")	    // <oMedTrans, nvarchar(max),>
                _T(",'%s'")	    // <oAddress, nvarchar(max),>
                _T(",'%s'")	    // <oCity, nvarchar(max),>
                _T(",'%s'")	    // <oState, nvarchar(max),>
                _T(",'%s'"), 	// <oZip, nvarchar(max),>)

                MakeOccupantKey(m_fileContent.summary.UCRNumber,
                                m_fileContent.vehicles[i].vVehNo,
                                m_fileContent.vehicles[i].Occupant[j].oSeatPos,
                                m_fileContent.vehicles[i].Occupant[j].oFirstName,
                                m_fileContent.vehicles[i].Occupant[j].oLastName,
                                m_fileContent.vehicles[i].Occupant[j].oAge,
                                m_fileContent.vehicles[i].Occupant[j].oSex,
                                m_fileContent.vehicles[i].Occupant[j].oCity),
                m_fileContent.summary.UCRNumber,
                m_fileContent.summary.CrashDate,
                m_fileContent.vehicles[i].vVehNo,
                m_fileContent.vehicles[i].Occupant[j].oSeatPos,
                m_fileContent.vehicles[i].Occupant[j].oFirstName,
                m_fileContent.vehicles[i].Occupant[j].oLastName,
                m_fileContent.vehicles[i].Occupant[j].oMiddleName,
                m_fileContent.vehicles[i].Occupant[j].oAge,
                m_fileContent.vehicles[i].Occupant[j].oSex,
                m_fileContent.vehicles[i].Occupant[j].oRace,
                m_fileContent.vehicles[i].Occupant[j].oInjuryCode,
                m_fileContent.vehicles[i].Occupant[j].oOPCode,
                m_fileContent.vehicles[i].Occupant[j].OOPPROPERLYUSED,
                m_fileContent.vehicles[i].Occupant[j].oAirBagDeploy,
                m_fileContent.vehicles[i].Occupant[j].oEjected,
                m_fileContent.vehicles[i].Occupant[j].oEMSNum,
                m_fileContent.vehicles[i].Occupant[j].oMedTrans,
                m_fileContent.vehicles[i].Occupant[j].oAddress,
                m_fileContent.vehicles[i].Occupant[j].oCity,
                m_fileContent.vehicles[i].Occupant[j].oState,
                m_fileContent.vehicles[i].Occupant[j].oZip
                );
        
            strSql += strOccupant + _T("; ");
            ++j;
        }
    }

    return 0;
}

int CDataParser::GetSQL_vehicle(CString& strSql)
{
    for (UINT i = 0; i < m_fileContent.NumberofVehicles; ++i)
    {
        CString strVeh;
        strVeh.Format(
            _T("INSERT INTO [dbo].[Avehicle2012]")
            _T("([ucrnumber]                    ")
            _T(",[vehno]                        ")
            _T(",[crashdate]                    ")
            _T(",[source]                       ")
            _T(",[DALC]                         ")
            _T(",[DRUG]                         ")
            _T(",[topcfcar]                     ")
            _T(",[typev]                        ")
            _T(",[dresid]                       ")
            _T(",[ACFAvoidNoContactOther]       ")
            _T(",[ACFAvoidNoContactVe]          ")
            _T(",[ACFCellPhone]                 ")
            _T(",[ACFDefectiveSteering]         ")
            _T(",[ACFDefectiveTires]            ")
            _T(",[ACFDisregardedTrafficSignal]  ")
            _T(",[ACFDriverInattention]         ")
            _T(",[ACFDriverlessMovingVe]        ")
            _T(",[ACFDroveLeftOfCenter]         ")
            _T(",[ACFExcessiveSpeed]            ")
            _T(",[ACFFailedToYieldEmgcyVe]      ")
            _T(",[ACFFailedToYieldPoliceVe]     ")
            _T(",[ACFFailedToYieldRightOfWay]   ")
            _T(",[ACFFollowingTooClosely]       ")
            _T(",[ACFHighSpeedPursuit]          ")
            _T(",[ACFImproperBacking]           ")
            _T(",[ACFImproperLaneChange]        ")
            _T(",[ACFImproperOvertaking]        ")
            _T(",[ACFInadequateBrakes]          ")
            _T(",[ACFLowVisibilityDueToSmoke]   ")
            _T(",[ACFMadeImproperTurn]          ")
            _T(",[ACFNone]                      ")
            _T(",[ACFOtherImproperDriving]      ")
            _T(",[ACFOtherMechanicalDefect]     ")
            _T(",[ACFOtherNoDriverError]        ")
            _T(",[ACFPassedStopSign]            ")
            _T(",[ACFPedestrianError]           ")
            _T(",[ACFRoadDefect]                ")
            _T(",[ACFSpeed2FastForConditions]   ")
            _T(",[ACFTexting]                   ")
            _T(",[ACFTrafficControlInopMissing] ")
            _T(",[ACFUnderInflOfDrugs]          ")
            _T(",[ACFUnderInfluenceOfAlcohol]   ")
            _T(",[ACFVeSkiddedBeforeBrk]        ")
            _T(",[CarrierAddress]               ")
            _T(",[CarrierName]                  ")
            _T(",[CarrierZip]                   ")
            _T(",[ConditionAmputee]             ")
            _T(",[ConditionEyesightImpaired]    ")
            _T(",[ConditionFatiguedAsleep]      ")
            _T(",[ConditionHearingImpaired]     ")
            _T(",[ConditionIllness]             ")
            _T(",[ConditionMedsDrugsAlcohol]    ")
            _T(",[ConditionNoAppDefects]        ")
            _T(",[ConditionOtherText]           ")
            _T(",[ConditionOther]               ")
            _T(",[ConditionUnknown]             ")
            _T(",[DABacking]                    ")
            _T(",[DAGoingStraight]              ")
            _T(",[DALeftTurn]                   ")
            _T(",[DAOther]                      ")
            _T(",[DAOvertakingPassing]          ")
            _T(",[DAParked]                     ")
            _T(",[DARightTurn]                  ")
            _T(",[DASlowing]                    ")
            _T(",[DAStartFromPark]              ")
            _T(",[DAStartInTrafficLane]         ")
            _T(",[DAStoppedForSignsSignal]      ")
            _T(",[DAStoppedForTraffic]          ")
            _T(",[DAUnknown]                    ")
            _T(",[DAUturn]                      ")
            _T(",[DLDoB]                        ")
            _T(",[DLEndorsements]               ")
            _T(",[DLExpires]                    ")
            _T(",[DLNumber]                     ")
            _T(",[DLRestrictions]               ")
            _T(",[DLState]                      ")
            _T(",[DLStatus]                     ")
            _T(",[DLType]                       ")
            _T(",[DrFirstName]                  ")
            _T(",[DrLastName]                   ")
            _T(",[DrSeatPos]                    ")
            _T(",[DrAge]                        ")
            _T(",[DrSex]                        ")
            _T(",[DrRace]                       ")
            _T(",[DrInjuryCode]                 ")
            _T(",[DrOPCode]                     ")
            _T(",[DrOPProperlyUsed]             ")
            _T(",[DrAirbagDeployed]             ")
            _T(",[DrEjected]                    ")
            _T(",[DrEMSNum]                     ")
            _T(",[DrMedTrans]                   ")
            _T(",[DrOccupation]                 ")
            _T(",[DrPhone]                      ")
            _T(",[DrMiddleName]                 ")
            _T(",[DrAddress]                    ")
            _T(",[DrCity]                       ")
            _T(",[DrZip]                        ")
            _T(",[GrossVehicleWeight]           ")
            _T(",[HazmatName]                   ")
            _T(",[HazmatPlacard]                ")
            _T(",[HazmatReleased]               ")
            _T(",[ICCCarrierCode]               ")
            _T(",[InsuredBy]                    ")
            _T(",[InterLock]                    ")
            _T(",[InterstateCarrier]            ")
            _T(",[LeftScene]                    ")
            _T(",[LiabilityInsurance]           ")
            _T(",[NumberofAxles]                ")
            _T(",[OwnersAddress]                ")
            _T(",[OwnersCompany]                ")
            _T(",[OwnersName]                   ")
            _T(",[OwnersPhone]                  ")
            _T(",[OwnersZip]                    ")
            _T(",[PedAtIntAgainstSignal]        ")
            _T(",[PedAtIntDiagonal]             ")
            _T(",[PedAtIntNoSignal]             ")
            _T(",[PedAtIntWithSignal]           ")
            _T(",[PedNotIntCrosswalk]           ")
            _T(",[PedNotIntFromBehindObstruct]  ")
            _T(",[PedNotIntNoCrosswalk]         ")
            _T(",[PedNotIntOtherText]           ")
            _T(",[PedNotIntOther]               ")
            _T(",[PedNotIntPlayinginRoad]       ")
            _T(",[PedNotIntPushWorkOnVe]        ")
            _T(",[PedNotIntStanding]            ")
            _T(",[PedNotIntWalkAgainstTraffic]  ")
            _T(",[PedNotIntWalkWithTraffic]     ")
            _T(",[PolicyNumber]                 ")
            _T(",[PostedSpeed]                  ")
            _T(",[RoadConditionsVe]             ")
            _T(",[RoadDesignDivider]            ")
            _T(",[RoadDesignLanes]              ")
            _T(",[RoadDesign]                   ")
            _T(",[RoadSurfaceVe]                ")
            _T(",[SafeSpeed]                    ")
            _T(",[SequenceEvent1]               ")
            _T(",[SequenceEvent2]               ")
            _T(",[SequenceEvent3]               ")
            _T(",[SequenceEvent4]               ")
            _T(",[SobrietyBAC]                  ")
            _T(",[SobrietyBloodTest]            ")
            _T(",[SobrietyBreathTest]           ")
            _T(",[SobrietyConsumeAlcohol]       ")
            _T(",[SobrietyConsumeCtrlSubtance]  ")
            _T(",[SobrietyConsumeMeds]          ")
            _T(",[SobrietyFieldSobrietyTest]    ")
            _T(",[SobrietyNotConsumeAlcohol]    ")
            _T(",[SobrietyTestByInst]           ")
            _T(",[SobrietyTestRefused]          ")
            _T(",[SobrietyUnknown]              ")
            _T(",[StreetOn]                     ")
            _T(",[TrafficControlDevice]         ")
            _T(",[Trailer1LicNumber]            ")
            _T(",[Trailer1LicYear]              ")
            _T(",[Trailer1Make]                 ")
            _T(",[Trailer1Type]                 ")
            _T(",[Trailer1Year]                 ")
            _T(",[Trailer2LicNumber]            ")
            _T(",[Trailer2LicYear]              ")
            _T(",[Trailer2Make]                 ")
            _T(",[Trailer2Type]                 ")
            _T(",[Trailer2Year]                 ")
            _T(",[Trailer3LicNumber]            ")
            _T(",[Trailer3LicYear]              ")
            _T(",[Trailer3Make]                 ")
            _T(",[Trailer3Type]                 ")
            _T(",[Trailer3Year]                 ")
            _T(",[USDOTNum]                     ")
            _T(",[vVehNo]                       ")
            _T(",[vLastName]                    ")
            _T(",[vFirstName]                   ")
            _T(",[vMiddleName]                  ")
            _T(",[vViolation]                   ")
            _T(",[vAction]                      ")
            _T(",[VeBodystyle]                  ")
            _T(",[VeCargoBody]                  ")
            _T(",[VeColor]                      ")
            _T(",[VeDamage10]                   ")
            _T(",[VeDamage11]                   ")
            _T(",[VeDamage12]                   ")
            _T(",[VeDamage1]                    ")
            _T(",[VeDamage2]                    ")
            _T(",[VeDamage3]                    ")
            _T(",[VeDamage4]                    ")
            _T(",[VeDamage5]                    ")
            _T(",[VeDamage6]                    ")
            _T(",[VeDamage7]                    ")
            _T(",[VeDamage8]                    ")
            _T(",[VeDamage9]                    ")
            _T(",[VeDamageAll]                  ")
            _T(",[VeDamageExtent]               ")
            _T(",[VeDamageNone]                 ")
            _T(",[VeDamageSeverity]             ")
            _T(",[VeDamageTop]                  ")
            _T(",[VeDamageUndercarriage]        ")
            _T(",[VeLicPlateNum]                ")
            _T(",[VeLicPlateRegYr]              ")
            _T(",[VeLicPlateState]              ")
            _T(",[VeMake]                       ")
            _T(",[VeTowedDisabled]              ")
            _T(",[VeTowed]                      ")
            _T(",[VeUse1]                       ")
            _T(",[VeUse2]                       ")
            _T(",[VehDirection]                 ")
            _T(",[veTowedBy]                    ")
            _T(",[veTowedTo]                    ")
            _T(",[veVin]                        ")
            _T(",[veYear])                      ")
            _T("VALUES")
            _T("(%d")		// <ucrnumber, float,>
            _T(",%d")		// <vehno, float,>
            _T(",'%s'")		// <crashdate, nvarchar(255),>
            _T(",'%s'")		// <source, nvarchar(max),>
            _T(",%d")		// <DALC, float,>
            _T(",%d")		// <DRUG, float,>
            _T(",%d")		// <topcfcar, float,>
            _T(",%d")		// <typev, float,>
            _T(",'%s'")		// <dresid, nvarchar(max),>
            _T(",%d")		// <ACFAvoidNoContactOther, float,>
            _T(",%d")		// <ACFAvoidNoContactVe, float,>
            _T(",%d")		// <ACFCellPhone, float,>
            _T(",%d")		// <ACFDefectiveSteering, float,>
            _T(",%d")		// <ACFDefectiveTires, float,>
            _T(",%d")		// <ACFDisregardedTrafficSignal, float
            _T(",%d")		// <ACFDriverInattention, float,>
            _T(",%d")		// <ACFDriverlessMovingVe, float,>
            _T(",%d")		// <ACFDroveLeftOfCenter, float,>
            _T(",%d")		// <ACFExcessiveSpeed, float,>
            _T(",%d")		// <ACFFailedToYieldEmgcyVe, float,>
            _T(",%d")		// <ACFFailedToYieldPoliceVe, float,>
            _T(",%d")		// <ACFFailedToYieldRightOfWay, float,
            _T(",%d")		// <ACFFollowingTooClosely, float,>
            _T(",%d")		// <ACFHighSpeedPursuit, float,>
            _T(",%d")		// <ACFImproperBacking, float,>
            _T(",%d")		// <ACFImproperLaneChange, float,>
            _T(",%d")		// <ACFImproperOvertaking, float,>
            _T(",%d")		// <ACFInadequateBrakes, float,>
            _T(",%d")		// <ACFLowVisibilityDueToSmoke, float,
            _T(",%d")		// <ACFMadeImproperTurn, float,>
            _T(",%d")		// <ACFNone, float,>
            _T(",%d")		// <ACFOtherImproperDriving, float,>
            _T(",%d")		// <ACFOtherMechanicalDefect, float,>
            _T(",%d")		// <ACFOtherNoDriverError, float,>
            _T(",%d")		// <ACFPassedStopSign, float,>
            _T(",%d")		// <ACFPedestrianError, float,>
            _T(",%d")		// <ACFRoadDefect, float,>
            _T(",%d")		// <ACFSpeed2FastForConditions, float,
            _T(",%d")		// <ACFTexting, float,>
            _T(",%d")		// <ACFTrafficControlInopMissing, floa
            _T(",%d")		// <ACFUnderInflOfDrugs, float,>
            _T(",%d")		// <ACFUnderInfluenceOfAlcohol, float,
            _T(",%d")		// <ACFVeSkiddedBeforeBrk, float,>
            _T(",'%s'")		// <CarrierAddress, nvarchar(max),>
            _T(",'%s'")		// <CarrierName, nvarchar(max),>
            _T(",'%d'")		// <CarrierZip, nvarchar(max),>
            _T(",%d")		// <ConditionAmputee, float,>
            _T(",%d")		// <ConditionEyesightImpaired, float,>
            _T(",%d")		// <ConditionFatiguedAsleep, float,>
            _T(",%d")		// <ConditionHearingImpaired, float,>
            _T(",%d")		// <ConditionIllness, float,>
            _T(",%d")		// <ConditionMedsDrugsAlcohol, float,>
            _T(",%d")		// <ConditionNoAppDefects, float,>
            _T(",'%d'")		// <ConditionOtherText, nvarchar(max),
            _T(",%d")		// <ConditionOther, float,>
            _T(",%d")		// <ConditionUnknown, float,>
            _T(",%d")		// <DABacking, float,>
            _T(",%d")		// <DAGoingStraight, float,>
            _T(",%d")		// <DALeftTurn, float,>
            _T(",%d")		// <DAOther, float,>
            _T(",%d")		// <DAOvertakingPassing, float,>
            _T(",%d")		// <DAParked, float,>
            _T(",%d")		// <DARightTurn, float,>
            _T(",%d")		// <DASlowing, float,>
            _T(",%d")		// <DAStartFromPark, float,>
            _T(",%d")		// <DAStartInTrafficLane, float,>
            _T(",%d")		// <DAStoppedForSignsSignal, float,>
            _T(",%d")		// <DAStoppedForTraffic, float,>
            _T(",%d")		// <DAUnknown, float,>
            _T(",%d")		// <DAUturn, float,>
            _T(",'%s'")		// <DLDoB, nvarchar(255),>
            _T(",'%s'")		// <DLEndorsements, nvarchar(max),>
            _T(",'%s'")		// <DLExpires, nvarchar(max),>
            _T(",'%s'")		// <DLNumber, nvarchar(max),>
            _T(",'%s'")		// <DLRestrictions, nvarchar(max),>
            _T(",'%s'")		// <DLState, nvarchar(max),>
            _T(",'%s'")		// <DLStatus, nvarchar(max),>
            _T(",'%s'")		// <DLType, nvarchar(max),>
            _T(",'%s'")		// <DrFirstName, nvarchar(max),>
            _T(",'%s'")		// <DrLastName, nvarchar(max),>
            _T(",'%s'")		// <DrSeatPos, nvarchar(max),>
            _T(",%d")		// <DrAge, float,>
            _T(",'%s'")		// <DrSex, nvarchar(max),>
            _T(",'%s'")		// <DrRace, nvarchar(max),>
            _T(",'%s'")		// <DrInjuryCode, nvarchar(max),>
            _T(",'%s'")		// <DrOPCode, nvarchar(max),>
            _T(",'%s'")		// <DrOPProperlyUsed, nvarchar(max),>
            _T(",'%s'")		// <DrAirbagDeployed, nvarchar(max),>
            _T(",'%s'")		// <DrEjected, nvarchar(max),>
            _T(",'%s'")		// <DrEMSNum, nvarchar(max),>
            _T(",'%s'")		// <DrMedTrans, nvarchar(max),>
            _T(",'%s'")		// <DrOccupation, nvarchar(max),>
            _T(",'%s'")		// <DrPhone, nvarchar(max),>
            _T(",'%s'")		// <DrMiddleName, nvarchar(max),>
            _T(",'%s'")		// <DrAddress, nvarchar(max),>
            _T(",'%s'")		// <DrCity, nvarchar(max),>
            _T(",'%d'")		// <DrZip, nvarchar(max),>
            _T(",'%s'")		// <GrossVehicleWeight, nvarchar(max),
            _T(",'%s'")		// <HazmatName, nvarchar(max),>
            _T(",'%s'")		// <HazmatPlacard, nvarchar(max),>
            _T(",'%s'")		// <HazmatReleased, nvarchar(max),>
            _T(",'%s'")		// <ICCCarrierCode, nvarchar(max),>
            _T(",'%s'")		// <InsuredBy, nvarchar(max),>
            _T(",'%s'")		// <InterLock, nvarchar(max),>
            _T(",'%s'")		// <InterstateCarrier, nvarchar(max),>
            _T(",'%s'")		// <LeftScene, nvarchar(max),>
            _T(",'%s'")		// <LiabilityInsurance, nvarchar(max),
            _T(",'%s'")		// <NumberofAxles, nvarchar(max),>
            _T(",'%s'")		// <OwnersAddress, nvarchar(max),>
            _T(",'%s'")		// <OwnersCompany, nvarchar(max),>
            _T(",'%s'")		// <OwnersName, nvarchar(max),>
            _T(",'%s'")		// <OwnersPhone, nvarchar(max),>
            _T(",'%d'")		// <OwnersZip, nvarchar(max),>
            _T(",%d")		// <PedAtIntAgainstSignal, float,>
            _T(",%d")		// <PedAtIntDiagonal, float,>
            _T(",%d")		// <PedAtIntNoSignal, float,>
            _T(",%d")		// <PedAtIntWithSignal, float,>
            _T(",%d")		// <PedNotIntCrosswalk, float,>
            _T(",%d")		// <PedNotIntFromBehindObstruct, float
            _T(",%d")		// <PedNotIntNoCrosswalk, float,>
            _T(",%d")		// <PedNotIntOtherText, nvarchar(max),
            _T(",%d")		// <PedNotIntOther, float,>
            _T(",%d")		// <PedNotIntPlayinginRoad, float,>
            _T(",%d")		// <PedNotIntPushWorkOnVe, float,>
            _T(",%d")		// <PedNotIntStanding, float,>
            _T(",%d")		// <PedNotIntWalkAgainstTraffic, float
            _T(",%d")		// <PedNotIntWalkWithTraffic, float,>
            _T(",'%s'")		// <PolicyNumber, nvarchar(max),>
            _T(",'%d'")		// <PostedSpeed, nvarchar(max),>
            _T(",'%s'")		// <RoadConditionsVe, nvarchar(max),>
            _T(",'%s'")		// <RoadDesignDivider, nvarchar(max),>
            _T(",'%s'")		// <RoadDesignLanes, nvarchar(max),>
            _T(",'%s'")		// <RoadDesign, nvarchar(max),>
            _T(",'%s'")		// <RoadSurfaceVe, nvarchar(max),>
            _T(",'%d'")		// <SafeSpeed, nvarchar(max),>
            _T(",'%d'")		// <SequenceEvent1, nvarchar(max),>
            _T(",'%d'")		// <SequenceEvent2, nvarchar(max),>
            _T(",'%d'")		// <SequenceEvent3, nvarchar(max),>
            _T(",'%d'")		// <SequenceEvent4, nvarchar(max),>
            _T(",'%d'")		// <SobrietyBAC, nvarchar(max),>
            _T(",%d")		// <SobrietyBloodTest, float,>
            _T(",%d")		// <SobrietyBreathTest, float,>
            _T(",%d")		// <SobrietyConsumeAlcohol, float,>
            _T(",%d")		// <SobrietyConsumeCtrlSubtance, float
            _T(",%d")		// <SobrietyConsumeMeds, float,>
            _T(",%d")		// <SobrietyFieldSobrietyTest, float,>
            _T(",%d")		// <SobrietyNotConsumeAlcohol, float,>
            _T(",%d")		// <SobrietyTestByInst, float,>
            _T(",%d")		// <SobrietyTestRefused, float,>
            _T(",%d")		// <SobrietyUnknown, float,>
            _T(",'%s'")		// <StreetOn, nvarchar(max),>
            _T(",'%s'")		// <TrafficControlDevice, nvarchar(max
            _T(",'%s'")		// <Trailer1LicNumber, nvarchar(max),>
            _T(",'%s'")		// <Trailer1LicYear, nvarchar(max),>
            _T(",'%s'")		// <Trailer1Make, nvarchar(max),>
            _T(",'%s'")		// <Trailer1Type, nvarchar(max),>
            _T(",'%s'")		// <Trailer1Year, nvarchar(max),>
            _T(",'%s'")		// <Trailer2LicNumber, nvarchar(max),>
            _T(",'%s'")		// <Trailer2LicYear, nvarchar(max),>
            _T(",'%s'")		// <Trailer2Make, nvarchar(max),>
            _T(",'%s'")		// <Trailer2Type, nvarchar(max),>
            _T(",'%s'")		// <Trailer2Year, nvarchar(max),>
            _T(",'%s'")		// <Trailer3LicNumber, nvarchar(max),>
            _T(",'%s'")		// <Trailer3LicYear, nvarchar(max),>
            _T(",'%s'")		// <Trailer3Make, nvarchar(max),>
            _T(",'%s'")		// <Trailer3Type, nvarchar(max),>
            _T(",'%s'")		// <Trailer3Year, nvarchar(max),>
            _T(",'%d'")		// <USDOTNum, nvarchar(max),>
            _T(",'%d'")		// <vVehNo, nvarchar(max),>
            _T(",'%s'")		// <vLastName, nvarchar(max),>
            _T(",'%s'")		// <vFirstName, nvarchar(max),>
            _T(",'%s'")		// <vMiddleName, nvarchar(max),>
            _T(",'%s'")		// <vViolation, nvarchar(max),>
            _T(",'%s'")		// <vAction, nvarchar(max),>
            _T(",'%s'")		// <VeBodystyle, nvarchar(max),>
            _T(",'%s'")		// <VeCargoBody, nvarchar(max),>
            _T(",'%s'")		// <VeColor, nvarchar(max),>
            _T(",%d")		// <VeDamage10, float,>
            _T(",%d")		// <VeDamage11, float,>
            _T(",%d")		// <VeDamage12, float,>
            _T(",%d")		// <VeDamage1, float,>
            _T(",%d")		// <VeDamage2, float,>
            _T(",%d")		// <VeDamage3, float,>
            _T(",%d")		// <VeDamage4, float,>
            _T(",%d")		// <VeDamage5, float,>
            _T(",%d")		// <VeDamage6, float,>
            _T(",%d")		// <VeDamage7, float,>
            _T(",%d")		// <VeDamage8, float,>
            _T(",%d")		// <VeDamage9, float,>
            _T(",%d")		// <VeDamageAll, float,>
            _T(",'%s'")		// <VeDamageExtent, nvarchar(max),>
            _T(",%d")		// <VeDamageNone, float,>
            _T(",'%s'")		// <VeDamageSeverity, nvarchar(max),>
            _T(",%d")		// <VeDamageTop, float,>
            _T(",%d")		// <VeDamageUndercarriage, float,>
            _T(",'%s'")		// <VeLicPlateNum, nvarchar(max),>
            _T(",%d")		// <VeLicPlateRegYr, float,>
            _T(",'%s'")		// <VeLicPlateState, nvarchar(max),>
            _T(",'%s'")		// <VeMake, nvarchar(max),>
            _T(",'%s'")		// <VeTowedDisabled, nvarchar(max),>
            _T(",'%s'")		// <VeTowed, nvarchar(max),>
            _T(",'%s'")		// <VeUse1, nvarchar(max),>
            _T(",'%s'")		// <VeUse2, nvarchar(max),>
            _T(",'%s'")		// <VehDirection, nvarchar(max),>
            _T(",'%s'")		// <veTowedBy, nvarchar(max),>
            _T(",'%s'")		// <veTowedTo, nvarchar(max),>
            _T(",'%s'")		// <veVin, nvarchar(max),>
           _T(",%d)"), 		// <veYear, float,>)

            m_fileContent.summary.UCRNumber, 
            m_fileContent.vehicles[i].vVehNo, 
            m_fileContent.summary.CrashDate, 
            _T(""),     // source
            0,          // TODO DALC
            0,          // TODO DRUG
            0,          // TODO topcfcar
            0,          // TODO typev
            _T(""),     // TODO dressid
            m_fileContent.conditions[i].ACFAvoidNoContactOther, 
            m_fileContent.conditions[i].ACFAvoidNoContactVe, 
            m_fileContent.conditions[i].ACFCellPhone, 
            m_fileContent.conditions[i].ACFDefectiveSteering, 
            m_fileContent.conditions[i].ACFDefectiveTires, 
            m_fileContent.conditions[i].ACFDisregardedTrafficSignal, 
            m_fileContent.conditions[i].ACFDriverInattention, 
            m_fileContent.conditions[i].ACFDriverlessMovingVe, 
            m_fileContent.conditions[i].ACFDroveLeftOfCenter, 
            m_fileContent.conditions[i].ACFExcessiveSpeed, 
            m_fileContent.conditions[i].ACFFailedToYieldEmgcyVe, 
            m_fileContent.conditions[i].ACFFailedToYieldPoliceVe, 
            m_fileContent.conditions[i].ACFFailedToYieldRightOfWay, 
            m_fileContent.conditions[i].ACFFollowingTooClosely, 
            m_fileContent.conditions[i].ACFHighSpeedPursuit, 
            m_fileContent.conditions[i].ACFImproperBacking, 
            m_fileContent.conditions[i].ACFImproperLaneChange, 
            m_fileContent.conditions[i].ACFImproperOvertaking, 
            m_fileContent.conditions[i].ACFInadequateBrakes, 
            m_fileContent.conditions[i].ACFLowVisibilityDueToSmoke, 
            m_fileContent.conditions[i].ACFMadeImproperTurn, 
            m_fileContent.conditions[i].ACFNone, 
            m_fileContent.conditions[i].ACFOtherImproperDriving, 
            m_fileContent.conditions[i].ACFOtherMechanicalDefect, 
            m_fileContent.conditions[i].ACFOtherNoDriverError, 
            m_fileContent.conditions[i].ACFPassedStopSign, 
            m_fileContent.conditions[i].ACFPedestrianError, 
            m_fileContent.conditions[i].ACFRoadDefect, 
            m_fileContent.conditions[i].ACFSpeed2FastForConditions, 
            m_fileContent.conditions[i].ACFTexting, 
            m_fileContent.conditions[i].ACFTrafficControlInopMissing, 
            m_fileContent.conditions[i].ACFUnderInflOfDrugs, 
            m_fileContent.conditions[i].ACFUnderInfluenceOfAlcohol, 
            m_fileContent.conditions[i].ACFVeSkiddedBeforeBrk, 
            m_fileContent.vehicles[i].CarrierAddress, 
            m_fileContent.vehicles[i].CarrierName, 
            m_fileContent.vehicles[i].CarrierZip, 
            m_fileContent.conditions[i].ConditionAmputee, 
            m_fileContent.conditions[i].ConditionEyesightImpaired, 
            m_fileContent.conditions[i].ConditionFatiguedAsleep, 
            m_fileContent.conditions[i].ConditionHearingImpaired, 
            m_fileContent.conditions[i].ConditionIllness, 
            m_fileContent.conditions[i].ConditionMedsDrugsAlcohol, 
            m_fileContent.conditions[i].ConditionNoAppDefects, 
            m_fileContent.conditions[i].ConditionOtherText, 
            m_fileContent.conditions[i].ConditionOther, 
            m_fileContent.conditions[i].ConditionUnknown, 
            m_fileContent.conditions[i].DABacking, 
            m_fileContent.conditions[i].DAGoingStraight, 
            m_fileContent.conditions[i].DALeftTurn, 
            m_fileContent.conditions[i].DAOther, 
            m_fileContent.conditions[i].DAOvertakingPassing, 
            m_fileContent.conditions[i].DAParked, 
            m_fileContent.conditions[i].DARightTurn, 
            m_fileContent.conditions[i].DASlowing, 
            m_fileContent.conditions[i].DAStartFromPark, 
            m_fileContent.conditions[i].DAStartInTrafficLane, 
            m_fileContent.conditions[i].DAStoppedForSignsSignal, 
            m_fileContent.conditions[i].DAStoppedForTraffic, 
            m_fileContent.conditions[i].DAUnknown, 
            m_fileContent.conditions[i].DAUturn, 
            m_fileContent.vehicles[i].DLDoB, 
            m_fileContent.vehicles[i].DLEndorsements, 
            m_fileContent.vehicles[i].DLExpires, 
            m_fileContent.vehicles[i].DLNUMBER, 
            m_fileContent.vehicles[i].DLRestrictions, 
            m_fileContent.vehicles[i].DLState, 
            m_fileContent.vehicles[i].DLStatus, 
            m_fileContent.vehicles[i].DLType, 
            m_fileContent.vehicles[i].DRFIRSTNAME, 
            m_fileContent.vehicles[i].DRLASTNAME, 
            m_fileContent.vehicles[i].Driver.DRSeatPos, 
            m_fileContent.vehicles[i].Driver.DrAge, 
            m_fileContent.vehicles[i].Driver.DrSex, 
            m_fileContent.vehicles[i].Driver.DrRace, 
            m_fileContent.vehicles[i].Driver.DrInjuryCode, 
            m_fileContent.vehicles[i].Driver.DROPCODE, 
            m_fileContent.vehicles[i].Driver.DrOPProperlyUsed, 
            m_fileContent.vehicles[i].Driver.DrAirbagDeployed, 
            m_fileContent.vehicles[i].Driver.DrEjected, 
            m_fileContent.vehicles[i].Driver.DrEMSNum, 
            m_fileContent.vehicles[i].Driver.DrMedTrans, 
            m_fileContent.vehicles[i].Driver.DrOccupation, 
            m_fileContent.vehicles[i].DRPHONE, 
            m_fileContent.vehicles[i].DRMIDDLENAME, 
            m_fileContent.vehicles[i].DRADDRESS, 
            m_fileContent.vehicles[i].DRCITY, 
            m_fileContent.vehicles[i].DRZIP, 
            m_fileContent.vehicles[i].GrossVehicleWeight, 
            m_fileContent.vehicles[i].HazmatName, 
            m_fileContent.vehicles[i].HazmatPlacard, 
            m_fileContent.vehicles[i].HazmatReleased, 
            m_fileContent.vehicles[i].Vehicle.ICCCarrierCode, 
            m_fileContent.vehicles[i].Owner.InsuredBy, 
            _T(""),         // InterLock
            m_fileContent.vehicles[i].InterstateCarrier, 
            m_fileContent.vehicles[i].LeftScene, 
            _T(""),         // LiabilityInsurance
            m_fileContent.vehicles[i].NumberofAxles, 
            m_fileContent.vehicles[i].Owner.OwnersAddress, 
            m_fileContent.vehicles[i].Owner.OwnersCompany, 
            m_fileContent.vehicles[i].Owner.OwnersFirstName + m_fileContent.vehicles[i].Owner.OwnersMiddleName + m_fileContent.vehicles[i].Owner.OwnersLastName, 
            m_fileContent.vehicles[i].Owner.OWNERSPHONE, 
            m_fileContent.vehicles[i].Owner.OwnersZip, 
            m_fileContent.conditions[i].PedAtIntAgainstSignal, 
            m_fileContent.conditions[i].PedAtIntDiagonal, 
            m_fileContent.conditions[i].PedAtIntNoSignal, 
            m_fileContent.conditions[i].PedAtIntWithSignal, 
            m_fileContent.conditions[i].PedNotIntCrosswalk, 
            m_fileContent.conditions[i].PedNotIntFromBehindObstruct, 
            m_fileContent.conditions[i].PedNotIntNoCrosswalk, 
            m_fileContent.conditions[i].PedNotIntOtherText, 
            m_fileContent.conditions[i].PedNotIntOther, 
            m_fileContent.conditions[i].PedNotIntPlayinginRoad, 
            m_fileContent.conditions[i].PedNotIntPushWorkOnVe, 
            m_fileContent.conditions[i].PedNotIntStanding, 
            m_fileContent.conditions[i].PedNotIntWalkAgainstTraffic, 
            m_fileContent.conditions[i].PedNotIntWalkWithTraffic, 
            m_fileContent.vehicles[i].Owner.PolicyNumber, 
            m_fileContent.vehicles[i].PostedSpeed, 

            m_fileContent.conditions[i].RoadConditionsVe, 
            m_fileContent.conditions[i].RoadDesignDivider, 
            m_fileContent.conditions[i].RoadDesignLanes, 
            m_fileContent.conditions[i].RoadDesign, 
            m_fileContent.conditions[i].RoadSurfaceVe, 
            m_fileContent.vehicles[i].SafeSpeed, 
            m_fileContent.conditions[i].SequenceEvent1, 
            m_fileContent.conditions[i].SequenceEvent2,
            m_fileContent.conditions[i].SequenceEvent3,
            m_fileContent.conditions[i].SequenceEvent4,
            m_fileContent.conditions[i].SobrietyBAC, 
            m_fileContent.conditions[i].SobrietyBloodTest, 
            m_fileContent.conditions[i].SobrietyBreathTest, 
            m_fileContent.conditions[i].SobrietyConsumeAlcohol, 
            m_fileContent.conditions[i].SobrietyConsumeCtrlSubtance, 
            m_fileContent.conditions[i].SobrietyConsumeMeds, 
            m_fileContent.conditions[i].SobrietyFieldSobrietyTest, 
            m_fileContent.conditions[i].SobrietyNotConsumeAlcohol,
            m_fileContent.conditions[i].SobrietyTestByInst, 
            m_fileContent.conditions[i].SobrietyTestRefused, 
            m_fileContent.conditions[i].SobrietyUnknown, 
            m_fileContent.vehicles[i].StreetOn, 
            m_fileContent.conditions[i].TrafficControlDevice,
            m_fileContent.vehicles[i].Trailer[0].LicNumber,
            m_fileContent.vehicles[i].Trailer[0].LicYear,
            m_fileContent.vehicles[i].Trailer[0].Make,
            m_fileContent.vehicles[i].Trailer[0].Type,
            m_fileContent.vehicles[i].Trailer[0].Year,
            m_fileContent.vehicles[i].Trailer[1].LicNumber,
            m_fileContent.vehicles[i].Trailer[1].LicYear,
            m_fileContent.vehicles[i].Trailer[1].Make,
            m_fileContent.vehicles[i].Trailer[1].Type,
            m_fileContent.vehicles[i].Trailer[1].Year,
            m_fileContent.vehicles[i].Trailer[2].LicNumber,
            m_fileContent.vehicles[i].Trailer[2].LicYear,
            m_fileContent.vehicles[i].Trailer[2].Make,
            m_fileContent.vehicles[i].Trailer[2].Type,
            m_fileContent.vehicles[i].Trailer[2].Year,
            m_fileContent.vehicles[i].USDOTNum, 
            m_fileContent.vehicles[i].vVehNo, 
            m_fileContent.violations[0].vLastName, 
            m_fileContent.violations[0].vFirstName,
            m_fileContent.violations[0].vMiddleName, 
            m_fileContent.violations[0].vViolation, 
            m_fileContent.violations[0].vAction, 
            m_fileContent.vehicles[i].Vehicle.VeBodystyle, 
            m_fileContent.vehicles[i].Vehicle.VeCargoBody, 
            m_fileContent.vehicles[i].Vehicle.VeColor, 
            m_fileContent.vehicles[i].Vehicle.VeDamage[9],
            m_fileContent.vehicles[i].Vehicle.VeDamage[10],
            m_fileContent.vehicles[i].Vehicle.VeDamage[11],
            m_fileContent.vehicles[i].Vehicle.VeDamage[0],
            m_fileContent.vehicles[i].Vehicle.VeDamage[1],
            m_fileContent.vehicles[i].Vehicle.VeDamage[2],
            m_fileContent.vehicles[i].Vehicle.VeDamage[3],
            m_fileContent.vehicles[i].Vehicle.VeDamage[4],
            m_fileContent.vehicles[i].Vehicle.VeDamage[5],
            m_fileContent.vehicles[i].Vehicle.VeDamage[6],
            m_fileContent.vehicles[i].Vehicle.VeDamage[7],
            m_fileContent.vehicles[i].Vehicle.VeDamage[8],
            m_fileContent.vehicles[i].Vehicle.VeDamageAll, 
            m_fileContent.vehicles[i].Vehicle.VeDamageExtent, 
            m_fileContent.vehicles[i].Vehicle.VeDamageNone, 
            m_fileContent.vehicles[i].Vehicle.VeDamageSeverity, 
            m_fileContent.vehicles[i].Vehicle.VeDamageTop, 
            m_fileContent.vehicles[i].Vehicle.VeDamageUndercarriage, 
            m_fileContent.vehicles[i].Vehicle.VELICPLATENUM, 
            m_fileContent.vehicles[i].Vehicle.VELICPLATEREGYR, 
            m_fileContent.vehicles[i].Vehicle.VELICPLATESTATE, 
            m_fileContent.vehicles[i].Vehicle.VeMake, 
            m_fileContent.vehicles[i].Vehicle.VeTowedDisabled, 
            m_fileContent.vehicles[i].Vehicle.VeTowed, 
            m_fileContent.vehicles[i].Vehicle.VeUse1, 
            m_fileContent.vehicles[i].Vehicle.VeUse2, 
            m_fileContent.vehicles[i].VehDirection, 
            m_fileContent.vehicles[i].Vehicle.veTowedBy, 
            m_fileContent.vehicles[i].Vehicle.veTowedTo, 
            m_fileContent.vehicles[i].Vehicle.veVin, 
            m_fileContent.vehicles[i].Vehicle.veYear
            );

            strSql += strVeh + _T(";");
#ifdef DEBUG
            OutputDebugString(strSql.GetString());
#endif
    }

    return 0;
}

int CDataParser::WeekDayString2Int(const char* value, UINT& WeekDay)
{
    if (!_strnicmp(value, "Mon", strlen("Mon")))
    {
        WeekDay = 1;
    }
    else if (!_strnicmp(value, "Tues", strlen("Tues")))
    {
        WeekDay = 2;
    }
    else if (!_strnicmp(value, "Wed", strlen("Wed")))
    {
        WeekDay = 3;
    }
    else if (!_strnicmp(value, "Thur", strlen("Thur")))
    {
        WeekDay = 4;
    }
    else if (!_strnicmp(value, "Fri", strlen("Fri")))
    {
        WeekDay = 5;
    }
    else if (!_strnicmp(value, "Sat", strlen("Sat")))
    {
        WeekDay = 6;
    }
    else if (!_strnicmp(value, "Sun", strlen("Sun")))
    {
        WeekDay = 7;
    }
    else
    {
        ASSERT(0);
    }

    return 0;
}

CString CDataParser::MakeOccupantKey(UINT ucrNumber, UINT vehNo, CString& seatPos, CString& firstName, CString& lastName, UINT age, CString& sex, CString& city)
{
    CString key;
    key.Format(_T("%d%d%s%s%s%d%s%s"), ucrNumber, vehNo, seatPos, firstName, lastName, age, sex, city);

    return key;
}
