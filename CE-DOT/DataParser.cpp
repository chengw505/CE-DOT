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
}


int CDataParser::Parse(CString& strLocalFileName)
{
    Reset();
    m_strFileName = strLocalFileName;

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
        String2CTime(value, m_fileContent.summary.CrashDate);
    }
    else if (!_stricmp(key, "MilitaryTime"))
    {
        String2CTime(value, m_fileContent.summary.MilitaryTime);
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
        m_fileContent.summary.WeekDay = value;
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
        m_fileContent.summary.Measurement = value;
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
        String2CTime(value, m_fileContent.vehicles[i].DLExpires);
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
        m_fileContent.vehicles[i].DRPHONE = atoi(value);
    }
    else if (!_strnicmp(key, "DLDoB", strlen("DLDoB")))
    {
        ASSERT(key[strlen("DLDoB")] == '_');
        int i = atoi(&key[strlen("DLDoB") + 1]) - 1;
        String2CTime(value, m_fileContent.vehicles[i].DLDoB);
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
        String2CTime(value, m_fileContent.conclusion.TimeNotified);
    }
    else if (!_stricmp(key, "TimeArrived"))
    {
        String2CTime(value, m_fileContent.conclusion.TimeArrived);
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
        String2CTime(value, m_fileContent.conclusion.ReportDate);
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

int CDataParser::String2CTime(const char* value, CTime& time)
{
    return 0;
}
