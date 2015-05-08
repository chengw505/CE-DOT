USE [DOT]
GO

INSERT INTO [dbo].[Avehicle2012]
           ([ucrnumber]
           ,[vehno]
           ,[crashdate]
           ,[source]
           ,[DALC]
           ,[DRUG]
           ,[topcfcar]
           ,[typev]
           ,[dresid]
           ,[ACFAvoidNoContactOther]
           ,[ACFAvoidNoContactVe]
           ,[ACFCellPhone]
           ,[ACFDefectiveSteering]
           ,[ACFDefectiveTires]
           ,[ACFDisregardedTrafficSignal]
           ,[ACFDriverInattention]
           ,[ACFDriverlessMovingVe]
           ,[ACFDroveLeftOfCenter]
           ,[ACFExcessiveSpeed]
           ,[ACFFailedToYieldEmgcyVe]
           ,[ACFFailedToYieldPoliceVe]
           ,[ACFFailedToYieldRightOfWay]
           ,[ACFFollowingTooClosely]
           ,[ACFHighSpeedPursuit]
           ,[ACFImproperBacking]
           ,[ACFImproperLaneChange]
           ,[ACFImproperOvertaking]
           ,[ACFInadequateBrakes]
           ,[ACFLowVisibilityDueToSmoke]
           ,[ACFMadeImproperTurn]
           ,[ACFNone]
           ,[ACFOtherImproperDriving]
           ,[ACFOtherMechanicalDefect]
           ,[ACFOtherNoDriverError]
           ,[ACFPassedStopSign]
           ,[ACFPedestrianError]
           ,[ACFRoadDefect]
           ,[ACFSpeed2FastForConditions]
           ,[ACFTexting]
           ,[ACFTrafficControlInopMissing]
           ,[ACFUnderInflOfDrugs]
           ,[ACFUnderInfluenceOfAlcohol]
           ,[ACFVeSkiddedBeforeBrk]
           ,[CarrierAddress]
           ,[CarrierName]
           ,[CarrierZip]
           ,[ConditionAmputee]
           ,[ConditionEyesightImpaired]
           ,[ConditionFatiguedAsleep]
           ,[ConditionHearingImpaired]
           ,[ConditionIllness]
           ,[ConditionMedsDrugsAlcohol]
           ,[ConditionNoAppDefects]
           ,[ConditionOtherText]
           ,[ConditionOther]
           ,[ConditionUnknown]
           ,[DABacking]
           ,[DAGoingStraight]
           ,[DALeftTurn]
           ,[DAOther]
           ,[DAOvertakingPassing]
           ,[DAParked]
           ,[DARightTurn]
           ,[DASlowing]
           ,[DAStartFromPark]
           ,[DAStartInTrafficLane]
           ,[DAStoppedForSignsSignal]
           ,[DAStoppedForTraffic]
           ,[DAUnknown]
           ,[DAUturn]
           ,[DLDoB]
           ,[DLEndorsements]
           ,[DLExpires]
           ,[DLNumber]
           ,[DLRestrictions]
           ,[DLState]
           ,[DLStatus]
           ,[DLType]
           ,[DrFirstName]
           ,[DrLastName]
           ,[DrSeatPos]
           ,[DrAge]
           ,[DrSex]
           ,[DrRace]
           ,[DrInjuryCode]
           ,[DrOPCode]
           ,[DrOPProperlyUsed]
           ,[DrAirbagDeployed]
           ,[DrEjected]
           ,[DrEMSNum]
           ,[DrMedTrans]
           ,[DrOccupation]
           ,[DrPhone]
           ,[DrMiddleName]
           ,[DrAddress]
           ,[DrCity]
           ,[DrZip]
           ,[GrossVehicleWeight]
           ,[HazmatName]
           ,[HazmatPlacard]
           ,[HazmatReleased]
           ,[ICCCarrierCode]
           ,[InsuredBy]
           ,[InterLock]
           ,[InterstateCarrier]
           ,[LeftScene]
           ,[LiabilityInsurance]
           ,[NumberofAxles]
           ,[OwnersAddress]
           ,[OwnersCompany]
           ,[OwnersName]
           ,[OwnersPhone]
           ,[OwnersZip]
           ,[PedAtIntAgainstSignal]
           ,[PedAtIntDiagonal]
           ,[PedAtIntNoSignal]
           ,[PedAtIntWithSignal]
           ,[PedNotIntCrosswalk]
           ,[PedNotIntFromBehindObstruct]
           ,[PedNotIntNoCrosswalk]
           ,[PedNotIntOtherText]
           ,[PedNotIntOther]
           ,[PedNotIntPlayinginRoad]
           ,[PedNotIntPushWorkOnVe]
           ,[PedNotIntStanding]
           ,[PedNotIntWalkAgainstTraffic]
           ,[PedNotIntWalkWithTraffic]
           ,[PolicyNumber]
           ,[PostedSpeed]
           ,[RoadConditionsVe]
           ,[RoadDesignDivider]
           ,[RoadDesignLanes]
           ,[RoadDesign]
           ,[RoadSurfaceVe]
           ,[SafeSpeed]
           ,[SequenceEvent1]
           ,[SequenceEvent2]
           ,[SequenceEvent3]
           ,[SequenceEvent4]
           ,[SobrietyBAC]
           ,[SobrietyBloodTest]
           ,[SobrietyBreathTest]
           ,[SobrietyConsumeAlcohol]
           ,[SobrietyConsumeCtrlSubtance]
           ,[SobrietyConsumeMeds]
           ,[SobrietyFieldSobrietyTest]
           ,[SobrietyNotConsumeAlcohol]
           ,[SobrietyTestByInst]
           ,[SobrietyTestRefused]
           ,[SobrietyUnknown]
           ,[StreetOn]
           ,[TrafficControlDevice]
           ,[Trailer1LicNumber]
           ,[Trailer1LicYear]
           ,[Trailer1Make]
           ,[Trailer1Type]
           ,[Trailer1Year]
           ,[Trailer2LicNumber]
           ,[Trailer2LicYear]
           ,[Trailer2Make]
           ,[Trailer2Type]
           ,[Trailer2Year]
           ,[Trailer3LicNumber]
           ,[Trailer3LicYear]
           ,[Trailer3Make]
           ,[Trailer3Type]
           ,[Trailer3Year]
           ,[USDOTNum]
           ,[vVehNo]
           ,[vLastName]
           ,[vFirstName]
           ,[vMiddleName]
           ,[vViolation]
           ,[vAction]
           ,[VeBodystyle]
           ,[VeCargoBody]
           ,[VeColor]
           ,[VeDamage10]
           ,[VeDamage11]
           ,[VeDamage12]
           ,[VeDamage1]
           ,[VeDamage2]
           ,[VeDamage3]
           ,[VeDamage4]
           ,[VeDamage5]
           ,[VeDamage6]
           ,[VeDamage7]
           ,[VeDamage8]
           ,[VeDamage9]
           ,[VeDamageAll]
           ,[VeDamageExtent]
           ,[VeDamageNone]
           ,[VeDamageSeverity]
           ,[VeDamageTop]
           ,[VeDamageUndercarriage]
           ,[VeLicPlateNum]
           ,[VeLicPlateRegYr]
           ,[VeLicPlateState]
           ,[VeMake]
           ,[VeTowedDisabled]
           ,[VeTowed]
           ,[VeUse1]
           ,[VeUse2]
           ,[VehDirection]
           ,[veTowedBy]
           ,[veTowedTo]
           ,[veVin]
           ,[veYear])
     VALUES
           (<ucrnumber, float,>
           ,<vehno, float,>
           ,<crashdate, nvarchar(255),>
           ,<source, nvarchar(max),>
           ,<DALC, float,>
           ,<DRUG, float,>
           ,<topcfcar, float,>
           ,<typev, float,>
           ,<dresid, nvarchar(max),>
           ,<ACFAvoidNoContactOther, float,>
           ,<ACFAvoidNoContactVe, float,>
           ,<ACFCellPhone, float,>
           ,<ACFDefectiveSteering, float,>
           ,<ACFDefectiveTires, float,>
           ,<ACFDisregardedTrafficSignal, float,>
           ,<ACFDriverInattention, float,>
           ,<ACFDriverlessMovingVe, float,>
           ,<ACFDroveLeftOfCenter, float,>
           ,<ACFExcessiveSpeed, float,>
           ,<ACFFailedToYieldEmgcyVe, float,>
           ,<ACFFailedToYieldPoliceVe, float,>
           ,<ACFFailedToYieldRightOfWay, float,>
           ,<ACFFollowingTooClosely, float,>
           ,<ACFHighSpeedPursuit, float,>
           ,<ACFImproperBacking, float,>
           ,<ACFImproperLaneChange, float,>
           ,<ACFImproperOvertaking, float,>
           ,<ACFInadequateBrakes, float,>
           ,<ACFLowVisibilityDueToSmoke, float,>
           ,<ACFMadeImproperTurn, float,>
           ,<ACFNone, float,>
           ,<ACFOtherImproperDriving, float,>
           ,<ACFOtherMechanicalDefect, float,>
           ,<ACFOtherNoDriverError, float,>
           ,<ACFPassedStopSign, float,>
           ,<ACFPedestrianError, float,>
           ,<ACFRoadDefect, float,>
           ,<ACFSpeed2FastForConditions, float,>
           ,<ACFTexting, float,>
           ,<ACFTrafficControlInopMissing, float,>
           ,<ACFUnderInflOfDrugs, float,>
           ,<ACFUnderInfluenceOfAlcohol, float,>
           ,<ACFVeSkiddedBeforeBrk, float,>
           ,<CarrierAddress, nvarchar(max),>
           ,<CarrierName, nvarchar(max),>
           ,<CarrierZip, nvarchar(max),>
           ,<ConditionAmputee, float,>
           ,<ConditionEyesightImpaired, float,>
           ,<ConditionFatiguedAsleep, float,>
           ,<ConditionHearingImpaired, float,>
           ,<ConditionIllness, float,>
           ,<ConditionMedsDrugsAlcohol, float,>
           ,<ConditionNoAppDefects, float,>
           ,<ConditionOtherText, nvarchar(max),>
           ,<ConditionOther, float,>
           ,<ConditionUnknown, float,>
           ,<DABacking, float,>
           ,<DAGoingStraight, float,>
           ,<DALeftTurn, float,>
           ,<DAOther, float,>
           ,<DAOvertakingPassing, float,>
           ,<DAParked, float,>
           ,<DARightTurn, float,>
           ,<DASlowing, float,>
           ,<DAStartFromPark, float,>
           ,<DAStartInTrafficLane, float,>
           ,<DAStoppedForSignsSignal, float,>
           ,<DAStoppedForTraffic, float,>
           ,<DAUnknown, float,>
           ,<DAUturn, float,>
           ,<DLDoB, nvarchar(255),>
           ,<DLEndorsements, nvarchar(max),>
           ,<DLExpires, nvarchar(max),>
           ,<DLNumber, nvarchar(max),>
           ,<DLRestrictions, nvarchar(max),>
           ,<DLState, nvarchar(max),>
           ,<DLStatus, nvarchar(max),>
           ,<DLType, nvarchar(max),>
           ,<DrFirstName, nvarchar(max),>
           ,<DrLastName, nvarchar(max),>
           ,<DrSeatPos, nvarchar(max),>
           ,<DrAge, float,>
           ,<DrSex, nvarchar(max),>
           ,<DrRace, nvarchar(max),>
           ,<DrInjuryCode, nvarchar(max),>
           ,<DrOPCode, nvarchar(max),>
           ,<DrOPProperlyUsed, nvarchar(max),>
           ,<DrAirbagDeployed, nvarchar(max),>
           ,<DrEjected, nvarchar(max),>
           ,<DrEMSNum, nvarchar(max),>
           ,<DrMedTrans, nvarchar(max),>
           ,<DrOccupation, nvarchar(max),>
           ,<DrPhone, nvarchar(max),>
           ,<DrMiddleName, nvarchar(max),>
           ,<DrAddress, nvarchar(max),>
           ,<DrCity, nvarchar(max),>
           ,<DrZip, nvarchar(max),>
           ,<GrossVehicleWeight, nvarchar(max),>
           ,<HazmatName, nvarchar(max),>
           ,<HazmatPlacard, nvarchar(max),>
           ,<HazmatReleased, nvarchar(max),>
           ,<ICCCarrierCode, nvarchar(max),>
           ,<InsuredBy, nvarchar(max),>
           ,<InterLock, nvarchar(max),>
           ,<InterstateCarrier, nvarchar(max),>
           ,<LeftScene, nvarchar(max),>
           ,<LiabilityInsurance, nvarchar(max),>
           ,<NumberofAxles, nvarchar(max),>
           ,<OwnersAddress, nvarchar(max),>
           ,<OwnersCompany, nvarchar(max),>
           ,<OwnersName, nvarchar(max),>
           ,<OwnersPhone, nvarchar(max),>
           ,<OwnersZip, nvarchar(max),>
           ,<PedAtIntAgainstSignal, float,>
           ,<PedAtIntDiagonal, float,>
           ,<PedAtIntNoSignal, float,>
           ,<PedAtIntWithSignal, float,>
           ,<PedNotIntCrosswalk, float,>
           ,<PedNotIntFromBehindObstruct, float,>
           ,<PedNotIntNoCrosswalk, float,>
           ,<PedNotIntOtherText, nvarchar(max),>
           ,<PedNotIntOther, float,>
           ,<PedNotIntPlayinginRoad, float,>
           ,<PedNotIntPushWorkOnVe, float,>
           ,<PedNotIntStanding, float,>
           ,<PedNotIntWalkAgainstTraffic, float,>
           ,<PedNotIntWalkWithTraffic, float,>
           ,<PolicyNumber, nvarchar(max),>
           ,<PostedSpeed, nvarchar(max),>
           ,<RoadConditionsVe, nvarchar(max),>
           ,<RoadDesignDivider, nvarchar(max),>
           ,<RoadDesignLanes, nvarchar(max),>
           ,<RoadDesign, nvarchar(max),>
           ,<RoadSurfaceVe, nvarchar(max),>
           ,<SafeSpeed, nvarchar(max),>
           ,<SequenceEvent1, nvarchar(max),>
           ,<SequenceEvent2, nvarchar(max),>
           ,<SequenceEvent3, nvarchar(max),>
           ,<SequenceEvent4, nvarchar(max),>
           ,<SobrietyBAC, nvarchar(max),>
           ,<SobrietyBloodTest, float,>
           ,<SobrietyBreathTest, float,>
           ,<SobrietyConsumeAlcohol, float,>
           ,<SobrietyConsumeCtrlSubtance, float,>
           ,<SobrietyConsumeMeds, float,>
           ,<SobrietyFieldSobrietyTest, float,>
           ,<SobrietyNotConsumeAlcohol, float,>
           ,<SobrietyTestByInst, float,>
           ,<SobrietyTestRefused, float,>
           ,<SobrietyUnknown, float,>
           ,<StreetOn, nvarchar(max),>
           ,<TrafficControlDevice, nvarchar(max),>
           ,<Trailer1LicNumber, nvarchar(max),>
           ,<Trailer1LicYear, nvarchar(max),>
           ,<Trailer1Make, nvarchar(max),>
           ,<Trailer1Type, nvarchar(max),>
           ,<Trailer1Year, nvarchar(max),>
           ,<Trailer2LicNumber, nvarchar(max),>
           ,<Trailer2LicYear, nvarchar(max),>
           ,<Trailer2Make, nvarchar(max),>
           ,<Trailer2Type, nvarchar(max),>
           ,<Trailer2Year, nvarchar(max),>
           ,<Trailer3LicNumber, nvarchar(max),>
           ,<Trailer3LicYear, nvarchar(max),>
           ,<Trailer3Make, nvarchar(max),>
           ,<Trailer3Type, nvarchar(max),>
           ,<Trailer3Year, nvarchar(max),>
           ,<USDOTNum, nvarchar(max),>
           ,<vVehNo, nvarchar(max),>
           ,<vLastName, nvarchar(max),>
           ,<vFirstName, nvarchar(max),>
           ,<vMiddleName, nvarchar(max),>
           ,<vViolation, nvarchar(max),>
           ,<vAction, nvarchar(max),>
           ,<VeBodystyle, nvarchar(max),>
           ,<VeCargoBody, nvarchar(max),>
           ,<VeColor, nvarchar(max),>
           ,<VeDamage10, float,>
           ,<VeDamage11, float,>
           ,<VeDamage12, float,>
           ,<VeDamage1, float,>
           ,<VeDamage2, float,>
           ,<VeDamage3, float,>
           ,<VeDamage4, float,>
           ,<VeDamage5, float,>
           ,<VeDamage6, float,>
           ,<VeDamage7, float,>
           ,<VeDamage8, float,>
           ,<VeDamage9, float,>
           ,<VeDamageAll, float,>
           ,<VeDamageExtent, nvarchar(max),>
           ,<VeDamageNone, float,>
           ,<VeDamageSeverity, nvarchar(max),>
           ,<VeDamageTop, float,>
           ,<VeDamageUndercarriage, float,>
           ,<VeLicPlateNum, nvarchar(max),>
           ,<VeLicPlateRegYr, float,>
           ,<VeLicPlateState, nvarchar(max),>
           ,<VeMake, nvarchar(max),>
           ,<VeTowedDisabled, nvarchar(max),>
           ,<VeTowed, nvarchar(max),>
           ,<VeUse1, nvarchar(max),>
           ,<VeUse2, nvarchar(max),>
           ,<VehDirection, nvarchar(max),>
           ,<veTowedBy, nvarchar(max),>
           ,<veTowedTo, nvarchar(max),>
           ,<veVin, nvarchar(max),>
           ,<veYear, float,>)
GO

