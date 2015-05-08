#pragma once

#define MAX_XML_ITEM_NUM 5

typedef struct
{
    CString Agency;
    UINT UCRNumber;
    UINT PrivateProperty;
    UINT Fatal_Injury;
    UINT Hit_Run;
    UINT NMDOTNumber;
    UINT CADNumber;
    CTime CrashDate;
    CTime MilitaryTime;
    UINT County;
    CString City;
    CString TribalJurisdiction;
    CString WeekDay;
    CString STREETA;
    CString INTERSECTING_STREETB;
    CString Measurement;
    CString MeasurementUnit;
    CString DirectionFromLandmark;
    CString Landmark;
    CString Milepost;
    CString Latitude;
    CString Longitude;
    CString CRASHOCCURRENCE;
    CString CrashClassification;
    CString AnalysisCode;
    CString Lighting;
    CString WEATHER;
    CString RoadCharacter;
    CString RoadGrade;

    void Reset()
    {
        UCRNumber = 0;
    }
}T_Summary;

typedef struct
{
    CString LiteralDescription;
    CString XCoordinate;
    CString YCoordinate;
}T_Location;

typedef struct
{
    UINT vVehNo;
    CString DrSex;
    CString DrRace;
    CString VehDirection;
    CString StreetOn;
    CString LeftScene;
    CString UnitType;
    UINT PostedSpeed;
    UINT SafeSpeed;
    CString DRFIRSTNAME;
    CString DRLASTNAME;
    CString DRMIDDLENAME;
    CString DRADDRESS;
    CString DLNUMBER;
    CString DLState;
    CString DLType;
    CString DLStatus;
    CString DLRestrictions;
    CString DLEndorsements;
    CTime DLExpires;
    CString DRCITY;
    CString DRSTATE;
    UINT DRZIP;
    UINT DRPHONE;
    CTime DLDoB;

    struct  
    {
        CString DrOccupation;
        CString DRSeatPos;
        CString DRSSN;
        UINT DrAge;
        CString DrSex;
        CString DrRace;
        CString DrInjuryCode;
        CString DROPCODE;
        CString DrOPProperlyUsed;
        CString DrAirbagDeployed;
        CString DrEjected;
        CString DrEMSNum;
        CString DrMedTrans;
    }Driver;

    struct
    {
        CString oSeatPos;
        CString oLastName;
        CString oFirstName;
        CString oMiddleName;
        UINT oAge;
        CString oSex;
        CString oRace;
        CString oInjuryCode;
        CString OOPPROPERLYUSED;
        CString oOPCode;
        CString oAirBagDeploy;
        CString oEjected;
        CString oEMSNum;
        CString oMedTrans;
        CString oAddress;
        CString oCity;
        CString oState;
        CString oZip;
    }Occupant[MAX_XML_ITEM_NUM];

    struct
    {
        UINT veYear;
        CString VeMake;
        CString VeColor;
        CString VeBodystyle;
        CString VeCargoBody;
        CString VeUse1;
        CString VeUse2;
        CString ICCCarrierCode;
        CString VELICPLATEREGYR;
        CString VELICPLATESTATE;
        CString VELICPLATENUM;
        CString veVin;
        CString VeTowed;
        CString veTowedBy;
        CString veTowedTo;
        CString VeTowedDisabled;
        CString VeDamageSeverity;
        CString VeDamageExtent;
        UINT VeDamage[13];
        UINT VeDamageAll;
        UINT VeDamageTop;
        UINT VeDamageUndercarriage;
        UINT VeDamageNone;
    }Vehicle;

    CString GrossVehicleWeight;
    CString HazmatPlacard;
    CString HazmatReleased;
    UINT USDOTNum;
    CString InterstateCarrier;
    CString NumberofAxles;
    CString HazmatName;
    CString CarrierName;
    CString CarrierAddress;
    UINT CarrierZip;
    struct  
    {
        CString OwnersFirstName;
        CString OwnersLastName;
        CString OwnersMiddleName;
        CString OwnersCompany;
        CString OwnersAddress;
        UINT  OwnersZip;
        CString OWNERSPHONE;
        CString InsuredBy;
        CString PolicyNumber;
    }Owner;

    struct {
        CString Type;
        CString Year;
        CString Make;
        CString LicYear;
        CString LicState;
        CString LicNumber;
    }Trailer[MAX_XML_ITEM_NUM];
}T_Vehicle;

typedef struct
{
    CString RoadConditionsVe;
    CString RoadSurfaceVe;
    CString TrafficControlDevice;
    CString RoadDesignLanes;
    CString RoadDesignDivider;
    CString RoadDesign;
    UINT ACFAvoidNoContactOther;
    UINT ACFAvoidNoContactVe;
    UINT ACFCellPhone;
    UINT ACFDefectiveSteering;
    UINT ACFDefectiveTires;
    UINT ACFDisregardedTrafficSignal;
    UINT ACFDriverInattention;
    UINT ACFDriverlessMovingVe;
    UINT ACFDroveLeftOfCenter;
    UINT ACFExcessiveSpeed;
    UINT ACFFailedToYieldEmgcyVe;
    UINT ACFFailedToYieldPoliceVe;
    UINT ACFFailedToYieldRightOfWay;
    UINT ACFFollowingTooClosely;
    UINT ACFHighSpeedPursuit;
    UINT ACFImproperBacking;
    UINT ACFImproperLaneChange;
    UINT ACFImproperOvertaking;
    UINT ACFInadequateBrakes;
    UINT ACFLowVisibilityDueToSmoke;
    UINT ACFMadeImproperTurn;
    UINT ACFNone;
    UINT ACFOtherImproperDriving;
    UINT ACFOtherMechanicalDefect;
    UINT ACFOtherNoDriverError;
    UINT ACFPassedStopSign;
    UINT ACFPedestrianError;
    UINT ACFRoadDefect;
    UINT ACFSpeed2FastForConditions;
    UINT ACFTexting;
    UINT ACFTrafficControlInopMissing;
    UINT ACFUnderInflOfDrugs;
    UINT ACFUnderInfluenceOfAlcohol;
    UINT ACFVeSkiddedBeforeBrk;
    UINT DABacking;
    UINT DAGoingStraight;
    UINT DALeftTurn;
    UINT DAOther;
    UINT DAOvertakingPassing;
    UINT DAParked;
    UINT DARightTurn;
    UINT DASlowing;
    UINT DAStartFromPark;
    UINT DAStartInTrafficLane;
    UINT DAStoppedForSignsSignal;
    UINT DAStoppedForTraffic;
    UINT DAUnknown;
    UINT DAUturn;
    UINT SequenceEvent1;
    UINT SequenceEvent2;
    UINT SequenceEvent3;
    UINT SequenceEvent4;
    UINT PedAtIntAgainstSignal;
    UINT PedAtIntDiagonal;
    UINT PedAtIntNoSignal;
    UINT PedAtIntWithSignal;
    UINT PedNotIntCrosswalk;
    UINT PedNotIntFromBehindObstruct;
    UINT PedNotIntNoCrosswalk;
    UINT PedNotIntOther;
    UINT PedNotIntPlayinginRoad;
    UINT PedNotIntPushWorkOnVe;
    UINT PedNotIntStanding;
    UINT PedNotIntWalkAgainstTraffic;
    UINT PedNotIntWalkWithTraffic;
    UINT PedNotIntOtherText;
    UINT ConditionAmputee;
    UINT ConditionEyesightImpaired;
    UINT ConditionFatiguedAsleep;
    UINT ConditionHearingImpaired;
    UINT ConditionIllness;
    UINT ConditionMedsDrugsAlcohol;
    UINT ConditionNoAppDefects;
    UINT ConditionOther;
    UINT ConditionUnknown;
    UINT ConditionOtherText;
    UINT SobrietyBAC;
    UINT SobrietyBloodTest;
    UINT SobrietyConsumeAlcohol;
    UINT SobrietyConsumeCtrlSubtance;
    UINT SobrietyConsumeMeds;
    UINT SobrietyFieldSobrietyTest;
    UINT SobrietyNotConsumeAlcohol;
    UINT SobrietyTestByInst;
    UINT SobrietyTestRefused;
    UINT SobrietyUnknown;
    UINT SobrietyBreathTest;
}T_Conditions;

typedef struct
{
    CString Narrative;
}T_Narrative;

typedef struct
{
    CString pType;
    CString pDesc;
    CString pLastName;
    CString pFirstName;
    CString pMiddleName;
    CString pAddress;
    CString pCity;
    CString pState;
    UINT pZip;
    CString pPhone;
}T_Property;

typedef struct
{
    CString vLastName;
    CString vFirstName;
    CString vMiddleName;
    CString vAction;
    CString vViolation;
}T_Violation;

typedef struct
{
    CTime TimeNotified;
    CTime TimeArrived;
    CString NotifiedBy;
    CString SupervisorOnScene;
    CString Checkedby;
    UINT OfficersSignaturePresent;
    UINT District;
    CTime ReportDate;
}T_Conclusion;

typedef struct
{
    CString DrawingsBy;
    CString MeasurementsTakenBy;

    void Reset()
    {
        DrawingsBy.Empty();
        MeasurementsTakenBy.Empty();
    }
}T_Diamgram;

typedef struct 
{
    UINT CaseNumber;
    CString OfficerAtScene;
    UINT BadgeNumber;
    UINT Agency;
    UINT NumberofVehicles;
    UINT NumberofDrawings;
    UINT PropertyDamage;
    UINT WitnessPresent;

    T_Summary summary;
    T_Location location;
    T_Vehicle vehicles[MAX_XML_ITEM_NUM];
    T_Conditions conditions[MAX_XML_ITEM_NUM];
    T_Narrative narrative;
    T_Property properties[MAX_XML_ITEM_NUM];
    T_Violation violations[MAX_XML_ITEM_NUM];
    T_Conclusion conclusion;
    T_Diamgram diagram;

    void Reset()
    {
        CaseNumber = 0;
        OfficerAtScene.Empty();
        BadgeNumber = 0;
        Agency = 0;
        NumberofVehicles = 0;
        NumberofDrawings = 0;
        PropertyDamage = 0;
        WitnessPresent = 0;
    }

    BOOL IsValid()
    {
        return CaseNumber != 0;
    }
}T_Form;

//////////////////////////////////////////////////////////////////////////

class CDataParser
{
public:
    CDataParser();
    ~CDataParser();

    CString m_strFileName;
    T_Form m_fileContent;

    void Reset();
    int Parse(CString& strLocalFileName);

private:
    int IsKeyElement(const char* key);
    int DispatchEntity(TiXmlNode* child);
    int FillForm(const char* key, const char* value);
    int FillSummary(TiXmlNode* child);
    int FillSummary(const char* key, const char* value);
    int FillVehicles(TiXmlNode* child);
    int FillVehicles(const char* key, const char* value);
    int FillConditions(TiXmlNode* child);
    int FillConditions(const char* key, const char* value);
    int FillNarrative(TiXmlNode* child);
    int FillNarrative(const char* key, const char* value);
    int FillProperties(TiXmlNode* child);
    int FillProperties(const char* key, const char* value);
    int FillViolations(TiXmlNode* child);
    int FillViolations(const char* key, const char* value);
    int FillConclusion(TiXmlNode* child);
    int FillConclusion(const char* key, const char* value);
    int FillDiagram(TiXmlNode* child);
    int FillDiagram(const char* key, const char* value);
    int FillLocation(TiXmlNode* root);
    int FillLocation(const char* key, const char* value);

    int String2CTime(const char* value, CTime& time);
};

