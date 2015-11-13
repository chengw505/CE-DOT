#pragma once

#define MAX_XML_ITEM_NUM 16

typedef struct
{
    CString Agency;
    UINT UCRNumber;
    UINT PrivateProperty;
    UINT Fatal_Injury;          // TODO report if this value > 0
    UINT Hit_Run;
    UINT NMDOTNumber;
    UINT CADNumber;
    CString CrashDate;
    CString MilitaryTime;
    UINT County;
    CString City;
    CString TribalJurisdiction;
    UINT WeekDay;
    CString STREETA;
    CString INTERSECTING_STREETB;
    UINT Measurement;
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
        Agency.Empty();
        UCRNumber = 0;
        UCRNumber = 0;
        PrivateProperty = 0;
        Fatal_Injury = 0;
        Hit_Run = 0;
        NMDOTNumber = 0;
        CADNumber = 0;
        CrashDate.Empty();
        MilitaryTime.Empty();
        County = 0;
        City.Empty();
        TribalJurisdiction.Empty();
        WeekDay = 0;
        STREETA.Empty();
        INTERSECTING_STREETB.Empty();
        Measurement = 0;
        MeasurementUnit.Empty();
        DirectionFromLandmark.Empty();
        Landmark.Empty();
        Milepost.Empty();
        Latitude.Empty();
        Longitude.Empty();
        CRASHOCCURRENCE.Empty();
        CrashClassification.Empty();
        AnalysisCode.Empty();
        Lighting.Empty();
        WEATHER.Empty();
        RoadCharacter.Empty();
        RoadGrade.Empty();
    }
}T_Summary;

typedef struct
{
    CString LiteralDescription;
    CString XCoordinate;
    CString YCoordinate;

    void Reset()
    {
        LiteralDescription.Empty();
        XCoordinate.Empty();
        YCoordinate.Empty();
    }
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
    CString DLExpires;
    CString DRCITY;
    CString DRSTATE;
    UINT DRZIP;
    CString DRPHONE;
    CString DLDoB;

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

        void Reset()
        {
            DrOccupation.Empty();
            DRSeatPos.Empty();
            DRSSN.Empty();
            DrAge = 0;
            DrSex.Empty();
            DrRace.Empty();
            DrInjuryCode.Empty();
            DROPCODE.Empty();
            DrOPProperlyUsed.Empty();
            DrAirbagDeployed.Empty();
            DrEjected.Empty();
            DrEMSNum.Empty();
            DrMedTrans.Empty();
        }
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

        void Reset()
        {
            oSeatPos.Empty();
            oLastName.Empty();
            oFirstName.Empty();
            oMiddleName.Empty();
            oAge = 0;
            oSex.Empty();
            oRace.Empty();
            oInjuryCode.Empty();
            OOPPROPERLYUSED.Empty();
            oOPCode.Empty();
            oAirBagDeploy.Empty();
            oEjected.Empty();
            oEMSNum.Empty();
            oMedTrans.Empty();
            oAddress.Empty();
            oCity.Empty();
            oState.Empty();
            oZip.Empty();
        }
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

        void Reset()
        {
            veYear = 0;
            VeMake.Empty();
            VeColor.Empty();
            VeBodystyle.Empty();
            VeCargoBody.Empty();
            VeUse1.Empty();
            VeUse2.Empty();
            ICCCarrierCode.Empty();
            VELICPLATEREGYR.Empty();
            VELICPLATESTATE.Empty();
            VELICPLATENUM.Empty();
            veVin.Empty();
            VeTowed.Empty();
            veTowedBy.Empty();
            veTowedTo.Empty();
            VeTowedDisabled.Empty();
            VeDamageSeverity.Empty();
            VeDamageExtent.Empty();
            memset(VeDamage, 0, sizeof(VeDamage));
            VeDamageAll = 0;
            VeDamageTop = 0;
            VeDamageUndercarriage = 0;
            VeDamageNone = 0;
        }
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

        void Reset()
        {
            OwnersFirstName.Empty();
            OwnersLastName.Empty();
            OwnersMiddleName.Empty();
            OwnersCompany.Empty();
            OwnersAddress.Empty();
            OwnersZip = 0;
            OWNERSPHONE.Empty();
            InsuredBy.Empty();
            PolicyNumber.Empty();
        }
    }Owner;

    struct {
        CString Type;
        CString Year;
        CString Make;
        CString LicYear;
        CString LicState;
        CString LicNumber;

        void Reset()
        {
            Type.Empty();
            Year.Empty();
            Make.Empty();
            LicYear.Empty();
            LicState.Empty();
            LicNumber.Empty();
        }
    }Trailer[MAX_XML_ITEM_NUM];

    void Reset()
    {
        vVehNo = 0;
        DrSex.Empty();
        DrRace.Empty();
        VehDirection.Empty();
        StreetOn.Empty();
        LeftScene.Empty();
        UnitType.Empty();
        PostedSpeed = 0;
        SafeSpeed = 0;
        DRFIRSTNAME.Empty();
        DRLASTNAME.Empty();
        DRMIDDLENAME.Empty();
        DRADDRESS.Empty();
        DLNUMBER.Empty();
        DLState.Empty();
        DLType.Empty();
        DLStatus.Empty();
        DLRestrictions.Empty();
        DLEndorsements.Empty();
        DLExpires.Empty();
        DRCITY.Empty();
        DRSTATE.Empty();
        DRZIP = 0;
        DRPHONE.Empty();
        DLDoB.Empty();

        Driver.Reset();
        Vehicle.Reset();

        GrossVehicleWeight.Empty();
        HazmatPlacard.Empty();
        HazmatReleased.Empty();
        USDOTNum = 0;
        InterstateCarrier.Empty();
        NumberofAxles.Empty();
        HazmatName.Empty();
        CarrierName.Empty();
        CarrierAddress.Empty();
        CarrierZip = 0;

        Owner.Reset();

        for (int i = 0; i < MAX_XML_ITEM_NUM; ++i)
        {
            Occupant[i].Reset();
            Trailer[i].Reset();
        }
    }

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

    void Reset()
    {
        RoadConditionsVe.Empty();
        RoadSurfaceVe.Empty();
        TrafficControlDevice.Empty();
        RoadDesignLanes.Empty();
        RoadDesignDivider.Empty();
        RoadDesign.Empty();
        ACFAvoidNoContactOther = 0;
        ACFAvoidNoContactVe = 0;
        ACFCellPhone = 0;
        ACFDefectiveSteering = 0;
        ACFDefectiveTires = 0;
        ACFDisregardedTrafficSignal = 0;
        ACFDriverInattention = 0;
        ACFDriverlessMovingVe = 0;
        ACFDroveLeftOfCenter = 0;
        ACFExcessiveSpeed = 0;
        ACFFailedToYieldEmgcyVe = 0;
        ACFFailedToYieldPoliceVe = 0;
        ACFFailedToYieldRightOfWay = 0;
        ACFFollowingTooClosely = 0;
        ACFHighSpeedPursuit = 0;
        ACFImproperBacking = 0;
        ACFImproperLaneChange = 0;
        ACFImproperOvertaking = 0;
        ACFInadequateBrakes = 0;
        ACFLowVisibilityDueToSmoke = 0;
        ACFMadeImproperTurn = 0;
        ACFNone = 0;
        ACFOtherImproperDriving = 0;
        ACFOtherMechanicalDefect = 0;
        ACFOtherNoDriverError = 0;
        ACFPassedStopSign = 0;
        ACFPedestrianError = 0;
        ACFRoadDefect = 0;
        ACFSpeed2FastForConditions = 0;
        ACFTexting = 0;
        ACFTrafficControlInopMissing = 0;
        ACFUnderInflOfDrugs = 0;
        ACFUnderInfluenceOfAlcohol = 0;
        ACFVeSkiddedBeforeBrk = 0;
        DABacking = 0;
        DAGoingStraight = 0;
        DALeftTurn = 0;
        DAOther = 0;
        DAOvertakingPassing = 0;
        DAParked = 0;
        DARightTurn = 0;
        DASlowing = 0;
        DAStartFromPark = 0;
        DAStartInTrafficLane = 0;
        DAStoppedForSignsSignal = 0;
        DAStoppedForTraffic = 0;
        DAUnknown = 0;
        DAUturn = 0;
        SequenceEvent1 = 0;
        SequenceEvent2 = 0;
        SequenceEvent3 = 0;
        SequenceEvent4 = 0;
        PedAtIntAgainstSignal = 0;
        PedAtIntDiagonal = 0;
        PedAtIntNoSignal = 0;
        PedAtIntWithSignal = 0;
        PedNotIntCrosswalk = 0;
        PedNotIntFromBehindObstruct = 0;
        PedNotIntNoCrosswalk = 0;
        PedNotIntOther = 0;
        PedNotIntPlayinginRoad = 0;
        PedNotIntPushWorkOnVe = 0;
        PedNotIntStanding = 0;
        PedNotIntWalkAgainstTraffic = 0;
        PedNotIntWalkWithTraffic = 0;
        PedNotIntOtherText = 0;
        ConditionAmputee = 0;
        ConditionEyesightImpaired = 0;
        ConditionFatiguedAsleep = 0;
        ConditionHearingImpaired = 0;
        ConditionIllness = 0;
        ConditionMedsDrugsAlcohol = 0;
        ConditionNoAppDefects = 0;
        ConditionOther = 0;
        ConditionUnknown = 0;
        ConditionOtherText = 0;
        SobrietyBAC = 0;
        SobrietyBloodTest = 0;
        SobrietyConsumeAlcohol = 0;
        SobrietyConsumeCtrlSubtance = 0;
        SobrietyConsumeMeds = 0;
        SobrietyFieldSobrietyTest = 0;
        SobrietyNotConsumeAlcohol = 0;
        SobrietyTestByInst = 0;
        SobrietyTestRefused = 0;
        SobrietyUnknown = 0;
        SobrietyBreathTest = 0;
    }

}T_Conditions;

typedef struct
{
    CString Narrative;

    void Reset()
    {
        Narrative.Empty();
    }
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

    void Reset()
    {
        pType.Empty();
        pDesc.Empty();
        pLastName.Empty();
        pFirstName.Empty();
        pMiddleName.Empty();
        pAddress.Empty();
        pCity.Empty();
        pState.Empty();
        pZip = 0;
        pPhone.Empty();
    }

}T_Property;

typedef struct
{
    CString vLastName;
    CString vFirstName;
    CString vMiddleName;
    CString vAction;
    CString vViolation;

    void Reset()
    {
        vLastName.Empty();
        vFirstName.Empty();
        vMiddleName.Empty();
        vAction.Empty();
        vViolation.Empty();
    }

}T_Violation;

typedef struct
{
    CString TimeNotified;
    CString TimeArrived;
    CString NotifiedBy;
    CString SupervisorOnScene;
    CString Checkedby;
    UINT OfficersSignaturePresent;
    UINT District;
    CString ReportDate;

    void Reset()
    {
        TimeNotified.Empty();
        TimeArrived.Empty();
        NotifiedBy.Empty();
        SupervisorOnScene.Empty();
        Checkedby.Empty();
        OfficersSignaturePresent = 0;
        District = 0;
        ReportDate.Empty();
    }
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

        summary.Reset();
        location.Reset();
        narrative.Reset();
        conclusion.Reset();
        diagram.Reset();

        for (int i = 0; i < MAX_XML_ITEM_NUM; ++i)
        {
            //vehicles[i].Reset();
            conditions[i].Reset();
            properties[i].Reset();
            violations[i].Reset();
        }
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
    CString m_ucrNumer;
    T_Form* m_fileContent;

    void Reset();
    int Parse(CString& strLocalFileName);

    UINT GetFatalInjury() { return m_fileContent->summary.Fatal_Injury; }
    CString GetClassification() { return m_fileContent->summary.CrashClassification; }
    BOOL CommercialVehicle() {
        for (int i = 0; i < m_fileContent->NumberofVehicles; ++i) {
            if (m_fileContent->vehicles[i].Vehicle.VeUse2 == "Commercial or business")    return TRUE;
        }
        return FALSE;
    }
    BOOL StateHighwayPropertyDamage() {
        for (int i = 0; i < m_fileContent->PropertyDamage; ++i) {
            if (m_fileContent->properties[i].pType == "H")   return TRUE;
        }
        return FALSE;
    }

    int GetUCRNumber(UINT& ucrNumber);
    CString GetUCRNumber() { return m_ucrNumer; }
    int GetSQL_crash(CString& strSql);
    int GetSQL_occupant(CString& strSql);
    int GetSQL_vehicle(CString& strSql);

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
    int Rollback(UINT urcNumber);
    int WeekDayString2Int(const char* value, UINT& WeekDay);
    CString MakeOccupantKey(UINT ucrNumber, 
        UINT vehNo, 
        CString& seatPos, 
        CString& firstName, 
        CString& lastName, 
        UINT age, 
        CString& sex, 
        CString& city);
    CString EscapeSQLString(const CString& strSql);
};
