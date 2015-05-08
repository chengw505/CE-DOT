USE [DOT]
GO

INSERT INTO [dbo].[Acrash2012]
           ([ucrnumber]
           ,[crashdate]
           ,[militarytime]
           ,[reportdate]
           ,[date_time]
           ,[ucrorig]
           ,[accdateorig]
           ,[agency]
           ,[agencyid]
           ,[analysiscode]
           ,[analysis]
           ,[batchnumber]
           ,[astreet]
           ,[bstreet]
           ,[landmark]
           ,[milepostKofax]
           ,[cadnumber]
           ,[casenumber]
           ,[checkedby]
           ,[city]
           ,[county]
           ,[urbnrurl]
           ,[Classification_Result]
           ,[CrashClassification]
           ,[CrashOccurrence]
           ,[DirectionFromLandmark]
           ,[District]
           ,[Fatal_Injury]
           ,[FormID]
           ,[FormMethod]
           ,[HitRun]
           ,[Latitude]
           ,[Lighting]
           ,[Longitude]
           ,[Measurement]
           ,[MeasurementsTakenBy]
           ,[MeasurementUnit]
           ,[NMDOTNumber]
           ,[NotifiedBy]
           ,[NumberofDrawings]
           ,[DrawingsBy]
           ,[NumberofVehicles]
           ,[OfficerAtScene]
           ,[OfficersSignaturePresent]
           ,[PrivateProperty]
           ,[PropertyDamage]
           ,[RoadCharacter]
           ,[RoadGrade]
           ,[StationReport]
           ,[SupervisorOnScene]
           ,[TimeArrived]
           ,[TimeNotified]
           ,[TribalJurisdiction]
           ,[Weather]
           ,[WeekDay]
           ,[WitnessPresent]
           ,[pDesc]
           ,[pType]
           ,[pAddress]
           ,[pCity]
           ,[pState]
           ,[pZip]
           ,[pPhone]
           ,[pFirstName]
           ,[pLastName]
           ,[pMiddleName]
           ,[FormIDKofax]
           ,[Year]
           ,[Month]
           ,[Hour]
           ,[nVeh]
           ,[Severity]
           ,[System]
           ,[topcfacc]
           ,[Alcinv]
           ,[Druginv]
           ,[MCinv]
           ,[PDinv]
           ,[PCinv]
           ,[TRKinv]
           ,[HZinv]
           ,[MotorVeh]
           ,[Killed]
           ,[Injured]
           ,[ClassA]
           ,[ClassB]
           ,[ClassC]
           ,[Unhurt]
           ,[Total]
           ,[Motorists]
           ,[NonMotorists]
           ,[GIS_Astreet]
           ,[GIS_Bstreet]
           ,[GIS_Location]
           ,[GIS_Route]
           ,[GIS_Milepost]
           ,[GIS_UrbanRural]
           ,[GIS_County]
           ,[GIS_CityE911]
           ,[GIS_CityUSCensus]
           ,[GIS_NatAmer_USCensus]
           ,[GIS_TransDist]
           ,[GIS_MaintDist]
           ,[GIS_UTM_X]
           ,[GIS_UTM_Y]
           ,[GIS_LAT]
           ,[GIS_LONG]
           ,[source]
           ,[NMDOTID]
           ,[SysBatchNumber]
           ,[SysScanDate])
     VALUES
           (<ucrnumber, float,>
           ,<crashdate, nvarchar(255),>
           ,<militarytime, nvarchar(255),>
           ,<reportdate, nvarchar(255),>
           ,<date_time, nvarchar(255),>
           ,<ucrorig, nvarchar(max),>
           ,<accdateorig, nvarchar(255),>
           ,<agency, nvarchar(max),>
           ,<agencyid, nvarchar(max),>
           ,<analysiscode, nvarchar(max),>
           ,<analysis, nvarchar(max),>
           ,<batchnumber, nvarchar(max),>
           ,<astreet, nvarchar(max),>
           ,<bstreet, nvarchar(max),>
           ,<landmark, nvarchar(max),>
           ,<milepostKofax, nvarchar(max),>
           ,<cadnumber, nvarchar(max),>
           ,<casenumber, nvarchar(max),>
           ,<checkedby, nvarchar(max),>
           ,<city, nvarchar(max),>
           ,<county, nvarchar(max),>
           ,<urbnrurl, nvarchar(max),>
           ,<Classification_Result, nvarchar(max),>
           ,<CrashClassification, nvarchar(max),>
           ,<CrashOccurrence, nvarchar(max),>
           ,<DirectionFromLandmark, nvarchar(max),>
           ,<District, nvarchar(max),>
           ,<Fatal_Injury, nvarchar(max),>
           ,<FormID, nvarchar(max),>
           ,<FormMethod, nvarchar(max),>
           ,<HitRun, nvarchar(max),>
           ,<Latitude, nvarchar(max),>
           ,<Lighting, nvarchar(max),>
           ,<Longitude, nvarchar(max),>
           ,<Measurement, float,>
           ,<MeasurementsTakenBy, nvarchar(max),>
           ,<MeasurementUnit, nvarchar(max),>
           ,<NMDOTNumber, nvarchar(max),>
           ,<NotifiedBy, nvarchar(max),>
           ,<NumberofDrawings, nvarchar(max),>
           ,<DrawingsBy, nvarchar(max),>
           ,<NumberofVehicles, float,>
           ,<OfficerAtScene, nvarchar(max),>
           ,<OfficersSignaturePresent, nvarchar(max),>
           ,<PrivateProperty, nvarchar(max),>
           ,<PropertyDamage, nvarchar(max),>
           ,<RoadCharacter, nvarchar(max),>
           ,<RoadGrade, nvarchar(max),>
           ,<StationReport, nvarchar(max),>
           ,<SupervisorOnScene, nvarchar(max),>
           ,<TimeArrived, nvarchar(255),>
           ,<TimeNotified, nvarchar(255),>
           ,<TribalJurisdiction, nvarchar(max),>
           ,<Weather, nvarchar(max),>
           ,<WeekDay, float,>
           ,<WitnessPresent, nvarchar(max),>
           ,<pDesc, nvarchar(max),>
           ,<pType, nvarchar(max),>
           ,<pAddress, nvarchar(max),>
           ,<pCity, nvarchar(max),>
           ,<pState, nvarchar(max),>
           ,<pZip, float,>
           ,<pPhone, nvarchar(max),>
           ,<pFirstName, nvarchar(max),>
           ,<pLastName, nvarchar(max),>
           ,<pMiddleName, nvarchar(max),>
           ,<FormIDKofax, nvarchar(max),>
           ,<Year, float,>
           ,<Month, float,>
           ,<Hour, float,>
           ,<nVeh, float,>
           ,<Severity, float,>
           ,<System, float,>
           ,<topcfacc, float,>
           ,<Alcinv, float,>
           ,<Druginv, float,>
           ,<MCinv, float,>
           ,<PDinv, float,>
           ,<PCinv, float,>
           ,<TRKinv, float,>
           ,<HZinv, float,>
           ,<MotorVeh, float,>
           ,<Killed, float,>
           ,<Injured, float,>
           ,<ClassA, float,>
           ,<ClassB, float,>
           ,<ClassC, float,>
           ,<Unhurt, float,>
           ,<Total, float,>
           ,<Motorists, float,>
           ,<NonMotorists, float,>
           ,<GIS_Astreet, nvarchar(max),>
           ,<GIS_Bstreet, nvarchar(max),>
           ,<GIS_Location, nvarchar(max),>
           ,<GIS_Route, nvarchar(max),>
           ,<GIS_Milepost, nvarchar(max),>
           ,<GIS_UrbanRural, nvarchar(max),>
           ,<GIS_County, nvarchar(max),>
           ,<GIS_CityE911, nvarchar(max),>
           ,<GIS_CityUSCensus, nvarchar(max),>
           ,<GIS_NatAmer_USCensus, nvarchar(max),>
           ,<GIS_TransDist, float,>
           ,<GIS_MaintDist, float,>
           ,<GIS_UTM_X, float,>
           ,<GIS_UTM_Y, float,>
           ,<GIS_LAT, float,>
           ,<GIS_LONG, float,>
           ,<source, nvarchar(max),>
           ,<NMDOTID, float,>
           ,<SysBatchNumber, nvarchar(max),>
           ,<SysScanDate, nvarchar(255),>)
GO

