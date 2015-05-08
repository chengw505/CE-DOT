USE [DOT]
GO

INSERT INTO [dbo].[Aoccupant2012]
           ([UCRVehnoPosFNLNAgeSexCity]
           ,[ucrnumber]
           ,[crashdate]
           ,[vehno]
           ,[oSeatPos]
           ,[oFirstName]
           ,[oLastName]
           ,[oMiddleName]
           ,[oAge]
           ,[oSex]
           ,[oRace]
           ,[oInjuryCode]
           ,[oOPCode]
           ,[oOPProperlyUsed]
           ,[oAirbagDeployed]
           ,[oEjected]
           ,[oEMSNum]
           ,[oMedTrans]
           ,[oAddress]
           ,[oCity]
           ,[oState]
           ,[oZip])
     VALUES
           (<UCRVehnoPosFNLNAgeSexCity, nvarchar(max),>
           ,<ucrnumber, float,>
           ,<crashdate, nvarchar(255),>
           ,<vehno, float,>
           ,<oSeatPos, nvarchar(max),>
           ,<oFirstName, nvarchar(max),>
           ,<oLastName, nvarchar(max),>
           ,<oMiddleName, nvarchar(max),>
           ,<oAge, float,>
           ,<oSex, nvarchar(max),>
           ,<oRace, nvarchar(max),>
           ,<oInjuryCode, nvarchar(max),>
           ,<oOPCode, nvarchar(max),>
           ,<oOPProperlyUsed, nvarchar(max),>
           ,<oAirbagDeployed, nvarchar(max),>
           ,<oEjected, nvarchar(max),>
           ,<oEMSNum, nvarchar(max),>
           ,<oMedTrans, nvarchar(max),>
           ,<oAddress, nvarchar(max),>
           ,<oCity, nvarchar(max),>
           ,<oState, nvarchar(max),>
           ,<oZip, nvarchar(max),>)
GO

