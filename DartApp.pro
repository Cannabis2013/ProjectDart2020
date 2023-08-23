QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += qml.qrc \

SOURCES += \
        DartsController/LocalDartsController/Controller/dartscontroller.cpp \
        DartsController/LocalDartsController/DartsAssemblers/assembledpc.cpp \
        DartsController/LocalDartsController/DartsAssemblers/assembledsc.cpp \
        DartsController/LocalDartsController/Finishes/dartscreatefinishes.cpp \
        DartsController/LocalDartsController/Finishes/dcfinishbuilder.cpp \
        DartsController/LocalDartsController/Finishes/defaultthresholds.cpp \
        DartsController/LocalDartsController/Index/dcindexconverter.cpp \
        DartsController/LocalDartsController/Index/dpcindexcontroller.cpp \
        DartsController/LocalDartsController/Index/dscindexcontroller.cpp \
        DartsController/LocalDartsController/Init/dcinitialize.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectfinclient.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectmetaclient.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcindexservices.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectiptservices.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectplaservices.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dscindexinjector.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinjectplaservives.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinputinjector.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdpcroutines.cpp \
        DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdscroutines.cpp \
        DartsController/LocalDartsController/Inputs/dcinputbuilder.cpp \
        DartsController/LocalDartsController/Inputs/dcinputconverter.cpp \
        DartsController/LocalDartsController/Inputs/dcjsontoinputmodels.cpp \
        DartsController/LocalDartsController/Inputs/dpcinputadder.cpp \
        DartsController/LocalDartsController/Inputs/dpcinputevaluator.cpp \
        DartsController/LocalDartsController/Inputs/dscinputadder.cpp \
        DartsController/LocalDartsController/Inputs/dscinputevaluator.cpp \
        DartsController/LocalDartsController/Meta/dcmetabuilder.cpp \
        DartsController/LocalDartsController/Meta/dcmetaconverter.cpp \
        DartsController/LocalDartsController/Players/dcconvertplayers.cpp \
        DartsController/LocalDartsController/Players/dcplayerbuilder.cpp \
        DartsController/LocalDartsController/Players/dcplayertojson.cpp \
        DartsController/LocalDartsController/Players/dpcplayerscontext.cpp \
        DartsController/LocalDartsController/Players/dscplayerscontext.cpp \
        DartsController/LocalDartsController/Routines/dcaddinput.cpp \
        DartsController/LocalDartsController/Routines/dccreatewinnerreport.cpp \
        DartsController/LocalDartsController/Routines/dcgetscoresasjson.cpp \
        DartsController/LocalDartsController/Routines/dcgetturnvaluesasjson.cpp \
        DartsController/LocalDartsController/Routines/dcredoturn.cpp \
        DartsController/LocalDartsController/Routines/dcresetservices.cpp \
        DartsController/LocalDartsController/Routines/dcundoturn.cpp \
        DartsController/LocalDartsController/localdartscontrollers.cpp \
        DartsModelsContext/Contracts/ByteArrayServices/converttobytearray.cpp \
        DartsModelsContext/LocalDartsModelsContext/dartscontext.cpp \
        DartsStatistics/DartsStatisticsImp/CreateDartsStatistics/dartsstatistics.cpp \
        DartsStatistics/DartsStatisticsImp/Injectors/createsnapshotsprovider.cpp \
        DartsStatistics/DartsStatisticsImp/Injectors/createstatisticprovider.cpp \
        DartsStatistics/DartsStatisticsImp/Injectors/createstatsservices.cpp \
        DartsStatistics/DartsStatisticsImp/Injectors/injectstatsroutines.cpp \
        DartsStatistics/DartsStatisticsImp/Inputs/createinput.cpp \
        DartsStatistics/DartsStatisticsImp/Inputs/inputsdb.cpp \
        DartsStatistics/DartsStatisticsImp/Players/createstatmodel.cpp \
        DartsStatistics/DartsStatisticsImp/Players/statsmemory.cpp \
        DartsStatistics/DartsStatisticsImp/Routines/createstatsreport.cpp \
        DartsStatistics/DartsStatisticsImp/Routines/removeinputfromcontext.cpp \
        DartsStatistics/DartsStatisticsImp/Routines/resetstatscontext.cpp \
        DartsStatistics/DartsStatisticsImp/Routines/updatecurrentstats.cpp \
        DartsStatistics/DartsStatisticsImp/Statistics/calculatemiddlevalue.cpp \
        DartsStatistics/DartsStatisticsImp/Statistics/updatescorerange.cpp \
        DartsStatistics/DartsStatisticsImp/CreateDartsStatistics/createdartsstatistics.cpp \
        DartsTableContext/dartstabledatacontext.cpp \
        DartsTableContext/dartstablemodel.cpp \
        DartsTableContext/dartstableslas.cpp \
        DartsModelsContext/LocalDartsModelsContext/DbServices/loadfromstorage.cpp \
        DartsModelsContext/LocalDartsModelsContext/DbServices/savetostorage.cpp \
        DartsModelsContext/LocalDartsModelsContext/IndexesServices/dartsindexbuilder.cpp \
        DartsModelsContext/LocalDartsModelsContext/Injectors/dartsindexinjector.cpp \
        DartsModelsContext/LocalDartsModelsContext/Injectors/dartsinputinjector.cpp \
        DartsModelsContext/LocalDartsModelsContext/Injectors/dartsplayerinjector.cpp \
        DartsModelsContext/LocalDartsModelsContext/Injectors/dartstournamentinjector.cpp \
        DartsModelsContext/LocalDartsModelsContext/Injectors/injectdartsroutines.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/countdartsinputs.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputbuilder.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputconverter.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputdb.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputstobytearray.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/getdartsinputs.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/removedartsinputs.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputs.cpp \
        DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputsbyindexes.cpp \
        DartsModelsContext/LocalDartsModelsContext/PlayerServices/dartsconvertplayer.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/addtournamenttodb.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartsaddinputtodb.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartsdisplayplayerinput.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartshideplayerinput.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartsinputtojson.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartsresettournament.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/dartstournamentrepair.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentasjson.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentsasjson.cpp \
        DartsModelsContext/LocalDartsModelsContext/Routines/removetournamentsfromdb.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsbuilder.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsjsonconverter.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsmetamodelbuilder.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartssetwinner.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsverifyconsistency.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartwinnermodelbuilder.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentfromdb.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentids.cpp \
        DartsModelsContext/LocalDartsModelsContext/TournamentsDbServices/dartsdbcontext.cpp \
        DartsModelsContext/LocalDartsModelsContext/localdartsmodelscontext.cpp \
        PlayerModelsContext/PlayerContextWithJson/CreatePlayerContext/playerscontext.cpp \
        PlayerModelsContext/PlayerContextWithJson/DataServices/plajsonbuilder.cpp \
        PlayerModelsContext/PlayerContextWithJson/DbServices/loadplayermodels.cpp \
        PlayerModelsContext/PlayerContextWithJson/DbServices/playersdbcontext.cpp \
        PlayerModelsContext/PlayerContextWithJson/DbServices/saveplayermodels.cpp \
        PlayerModelsContext/PlayerContextWithJson/ModelsServices/duplicatechecker.cpp \
        PlayerModelsContext/PlayerContextWithJson/Services/getplayersfromdb.cpp \
        PlayerModelsContext/PlayerContextWithJson/Services/plabuilder.cpp \
        PlayerModelsContext/PlayerContextWithJson/CreatePlayerContext/createplayerscontext.cpp \
        QmlContext/qmlpropertiesbuilder.cpp \
        Shared/filejsonio.cpp \
        main.cpp

HEADERS += \
    DartsController/Contracts/Controller/idartsctrl.h \
    DartsController/Contracts/Converters/idcjsontomodel.h \
    DartsController/Contracts/Converters/idcjsontomodels.h \
    DartsController/Contracts/Converters/idcmodeltojson.h \
    DartsController/Contracts/Finishes/dartsconstructslas.h \
    DartsController/Contracts/Finishes/dcfinishesservices.h \
    DartsController/Contracts/Finishes/idartsattemptsservice.h \
    DartsController/Contracts/Finishes/idartsboundaries.h \
    DartsController/Contracts/Finishes/idartscreatefinishes.h \
    DartsController/Contracts/Finishes/idartsdivisorvalues.h \
    DartsController/Contracts/Finishes/idartsfieldvalues.h \
    DartsController/Contracts/Finishes/idartsfinishesdb.h \
    DartsController/Contracts/Finishes/idartsmodidentifiers.h \
    DartsController/Contracts/Finishes/idartsterminaldivisor.h \
    DartsController/Contracts/Finishes/idartsthresholds.h \
    DartsController/Contracts/Finishes/idcfinishbuilder.h \
    DartsController/Contracts/Index/dcindexservices.h \
    DartsController/Contracts/Index/idcindexcontroller.h \
    DartsController/Contracts/Inputs/dcinputsservices.h \
    DartsController/Contracts/Inputs/idcinputadder.h \
    DartsController/Contracts/Inputs/idcinputbuilder.h \
    DartsController/Contracts/Inputs/idcinputconverter.h \
    DartsController/Contracts/Inputs/idcinputevaluator.h \
    DartsController/Contracts/Meta/dcmetaservices.h \
    DartsController/Contracts/Meta/idcmetabuilder.h \
    DartsController/Contracts/Meta/idcmetaconverter.h \
    DartsController/Contracts/Meta/idcmetamanager.h \
    DartsController/Contracts/Models/dcindex.h \
    DartsController/Contracts/Models/dcinput.h \
    DartsController/Contracts/Models/dcmeta.h \
    DartsController/Contracts/Models/dcplayer.h \
    DartsController/Contracts/Players/dcplayersservices.h \
    DartsController/Contracts/Players/idcplayermanager.h \
    DartsController/Contracts/Routines/dartscontrollerroutines.h \
    DartsController/Contracts/Routines/idcaddinput.h \
    DartsController/Contracts/Routines/idccreatewinnerjson.h \
    DartsController/Contracts/Routines/idcgetscoresasjson.h \
    DartsController/Contracts/Routines/idcgetturnvaluesasjson.h \
    DartsController/Contracts/Routines/idcinitialize.h \
    DartsController/Contracts/Routines/idcredoturn.h \
    DartsController/Contracts/Routines/idcresetservices.h \
    DartsController/Contracts/Routines/idcundoturn.h \
    DartsController/Contracts/ServicesProvider/dcservices.h \
    DartsController/LocalDartsController/Controller/dartscontroller.h \
    DartsController/LocalDartsController/DartsAssemblers/assembledpc.h \
    DartsController/LocalDartsController/DartsAssemblers/assembledsc.h \
    DartsController/LocalDartsController/Finishes/dartsboundaries.h \
    DartsController/LocalDartsController/Finishes/dartscreatefinishes.h \
    DartsController/LocalDartsController/Finishes/dartsdefaultattempts.h \
    DartsController/LocalDartsController/Finishes/dartsdivisors.h \
    DartsController/LocalDartsController/Finishes/dartsfieldvalues.h \
    DartsController/LocalDartsController/Finishes/dartsmodidentifiers.h \
    DartsController/LocalDartsController/Finishes/dartsterminaldivisor.h \
    DartsController/LocalDartsController/Finishes/dcfinishbuilder.h \
    DartsController/LocalDartsController/Finishes/dclogisticdb.h \
    DartsController/LocalDartsController/Finishes/defaultthresholds.h \
    DartsController/LocalDartsController/Index/dcindexconverter.h \
    DartsController/LocalDartsController/Index/dpcindexcontroller.h \
    DartsController/LocalDartsController/Index/dscindexcontroller.h \
    DartsController/LocalDartsController/Init/dcinitialize.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectfinclient.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dcinjectmetaclient.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcindexservices.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectiptservices.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dpcinjectplaservices.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dscindexinjector.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinjectplaservives.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/dscinputinjector.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdpcroutines.h \
    DartsController/LocalDartsController/DartsAssemblers/Injectors/injectdscroutines.h \
    DartsController/LocalDartsController/Inputs/dcinputbuilder.h \
    DartsController/LocalDartsController/Inputs/dcinputconverter.h \
    DartsController/LocalDartsController/Inputs/dcjsontoinputmodels.h \
    DartsController/LocalDartsController/Inputs/dpcinputadder.h \
    DartsController/LocalDartsController/Inputs/dpcinputevaluator.h \
    DartsController/LocalDartsController/Inputs/dscinputadder.h \
    DartsController/LocalDartsController/Inputs/dscinputevaluator.h \
    DartsController/LocalDartsController/Meta/dcmetabuilder.h \
    DartsController/LocalDartsController/Meta/dcmetaconverter.h \
    DartsController/LocalDartsController/Meta/dcmetaservice.h \
    DartsController/LocalDartsController/Meta/dcsettournamentid.h \
    DartsController/LocalDartsController/Players/dcconvertplayers.h \
    DartsController/LocalDartsController/Players/dcplayerbuilder.h \
    DartsController/LocalDartsController/Players/dcplayertojson.h \
    DartsController/LocalDartsController/Players/dpcplayerscontext.h \
    DartsController/LocalDartsController/Players/dscplayerscontext.h \
    DartsController/LocalDartsController/Routines/dcaddinput.h \
    DartsController/LocalDartsController/Routines/dccreatewinnerreport.h \
    DartsController/LocalDartsController/Routines/dcgetscoresasjson.h \
    DartsController/LocalDartsController/Routines/dcgetturnvaluesasjson.h \
    DartsController/LocalDartsController/Routines/dcredoturn.h \
    DartsController/LocalDartsController/Routines/dcresetservices.h \
    DartsController/LocalDartsController/Routines/dcundoturn.h \
    DartsController/LocalDartsController/localdartscontrollers.h \
    DartsModelsContext/Contracts/ByteArrayServices/converttobytearray.h \
    DartsModelsContext/Contracts/Db/idbcontext.h \
    DartsModelsContext/Contracts/Db/imodelconverter.h \
    DartsModelsContext/Contracts/Db/ifiledataio.h \
    DartsModelsContext/Contracts/Player/DartsPlayerServices.h \
    DartsModelsContext/Contracts/Player/IDartsConvertPlayer.h \
    DartsModelsContext/Contracts/Index/idartsindex.h \
    DartsModelsContext/Contracts/Index/dartsindexservices.h \
    DartsModelsContext/Contracts/Index/idartsindexbuilder.h \
    DartsModelsContext/Contracts/Input/idartsinput.h \
    DartsModelsContext/Contracts/Input/iplayerinput.h \
    DartsModelsContext/Contracts/Input/dartsinputservices.h \
    DartsModelsContext/Contracts/Input/icountinputmodels.h \
    DartsModelsContext/Contracts/Input/isortinputmodels.h \
    DartsModelsContext/Contracts/Input/idartsinputbuilder.h \
    DartsModelsContext/Contracts/Input/igetinputs.h \
    DartsModelsContext/Contracts/Input/iremovedartsinputs.h \
    DartsModelsContext/Contracts/Model/imodel.h \
    DartsModelsContext/Contracts/Player/DartsPlayer.h \
    DartsModelsContext/Contracts/Db/ipersistence.h \
    DartsModelsContext/Contracts/PredicateSLAs/imodelpredicate.h \
    DartsModelsContext/Contracts/Routines/IDartsAddTournament.h \
    DartsModelsContext/Contracts/Routines/IDartsHideInput.h \
    DartsModelsContext/Contracts/Routines/IDartsSetWinner.h \
    DartsModelsContext/Contracts/Routines/idartsaddinputtodb.h \
    DartsModelsContext/Contracts/Routines/idartsinputstojson.h \
    DartsModelsContext/Contracts/Routines/idartsinputtojson.h \
    DartsModelsContext/Contracts/Routines/idartsremovetournaments.h \
    DartsModelsContext/Contracts/Routines/idartsresettournament.h \
    DartsModelsContext/Contracts/Routines/idartsrevealinput.h \
    DartsModelsContext/Contracts/Routines/igettournamentasjson.h \
    DartsModelsContext/Contracts/Routines/igettournamentsasjson.h \
    DartsModelsContext/Contracts/Routines/itournamentrepair.h \
    DartsModelsContext/Contracts/abstractdartscontext.h \
    DartsModelsContext/Contracts/dartsmodelsroutines.h \
    DartsModelsContext/Contracts/dartsmodelsservices.h \
    DartsModelsContext/Contracts/Tournament/dartsmetamodel.h \
    DartsModelsContext/Contracts/Tournament/dartstournament.h \
    DartsModelsContext/Contracts/Tournament/idartstournament.h \
    DartsModelsContext/Contracts/Tournament/idartsbuilder.h \
    DartsModelsContext/Contracts/Tournament/igetdartstournament.h \
    DartsModelsContext/Contracts/Tournament/idartsconsistency.h \
    DartsModelsContext/Contracts/Tournament/idartscreatemeta.h \
    DartsModelsContext/Contracts/Tournament/idmcaddindexestotournament.h \
    DartsModelsContext/Contracts/Tournament/igettournamentids.h \
    DartsModelsContext/Contracts/Tournament/iwinnerinfobuilder.h \
    DartsModelsContext/Contracts/Tournament/tournamentservices.h \
    DartsModelsContext/LocalDartsModelsContext/dartscontext.h \
    DartsStatistics/Contracts/Db/istatsdb.h \
    DartsStatistics/Contracts/InputRoutines/IRemoveInputFromDb.h \
    DartsStatistics/Contracts/Inputs/Models/snapshot.h \
    DartsStatistics/Contracts/Inputs/icreatesnapshot.h \
    DartsStatistics/Contracts/Inputs/snapshotsservices.h \
    DartsStatistics/Contracts/Players/ICreateStatModel.h \
    DartsStatistics/Contracts/Players/Models/playerstats.h \
    DartsStatistics/Contracts/Players/statisticservices.h \
    DartsStatistics/Contracts/Report/icreatereport.h \
    DartsStatistics/Contracts/Routines/IUpdateCurrentStats.h \
    DartsStatistics/Contracts/Routines/iaddplayerstomem.h \
    DartsStatistics/Contracts/Routines/iresetmodels.h \
    DartsStatistics/Contracts/Routines/routineservices.h \
    DartsStatistics/Contracts/SLAs/idartsstatistics.h \
    DartsStatistics/Contracts/SLAs/servicescontext.h \
    DartsStatistics/Contracts/StatsServices/CalcAverage/ICalcAverage.h \
    DartsStatistics/Contracts/StatsServices/ScoreRange/iupdatescorerange.h \
    DartsStatistics/Contracts/StatsServices/StatsServices.h \
    DartsStatistics/DartsStatisticsImp/CreateDartsStatistics/dartsstatistics.h \
    DartsStatistics/DartsStatisticsImp/Injectors/createsnapshotsprovider.h \
    DartsStatistics/DartsStatisticsImp/Injectors/createstatisticprovider.h \
    DartsStatistics/DartsStatisticsImp/Injectors/createstatsservices.h \
    DartsStatistics/DartsStatisticsImp/Injectors/injectstatsroutines.h \
    DartsStatistics/DartsStatisticsImp/Inputs/createinput.h \
    DartsStatistics/DartsStatisticsImp/Inputs/inputsdb.h \
    DartsStatistics/DartsStatisticsImp/Players/createstatmodel.h \
    DartsStatistics/DartsStatisticsImp/Players/statsmemory.h \
    DartsStatistics/DartsStatisticsImp/Routines/createstatsreport.h \
    DartsStatistics/DartsStatisticsImp/Routines/removeinputfromcontext.h \
    DartsStatistics/DartsStatisticsImp/Routines/resetstatscontext.h \
    DartsStatistics/DartsStatisticsImp/Routines/updatecurrentstats.h \
    DartsStatistics/DartsStatisticsImp/Statistics/calculatemiddlevalue.h \
    DartsStatistics/DartsStatisticsImp/Statistics/updatescorerange.h \
    DartsStatistics/DartsStatisticsImp/CreateDartsStatistics/createdartsstatistics.h \
    DartsTableContext/DataContextSLAs/idartstabledatacontext.h \
    DartsTableContext/FontMetrics/greatestheight.h \
    DartsTableContext/FontMetrics/greatestwidth.h \
    DartsTableContext/FontMetrics/mhtablesectionmetrics.h \
    DartsTableContext/LinkedList/linkedlist.h \
    DartsTableContext/QMLDartsDataModel/dartsplayerdatamodel.h \
    DartsTableContext/QMLTableMetrics/mhtablecolumnwidth.h \
    DartsTableContext/QMLTableMetrics/mhtablerowheight.h \
    DartsTableContext/TableCellsServices/dartsinitrowvalues.h \
    DartsTableContext/TableSectionsSLAs/itablecellcontext.h \
    DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h \
    DartsTableContext/TableSectionsSLAs/itablesectioncontext.h \
    DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h \
    DartsTableContext/createqmlvariants.h \
    DartsTableContext/dartsdatacontextitemutility.h \
    DartsTableContext/dartstablecellcontext.h \
    DartsTableContext/dartstablecreatecolumnindices.h \
    DartsTableContext/dartstablecreatecolumns.h \
    DartsTableContext/dartstablecreaterowindices.h \
    DartsTableContext/dartstabledatacontext.h \
    DartsTableContext/dartstabledimensions.h \
    DartsTableContext/dartstablemodel.h \
    DartsTableContext/dartstablesectionmanipulator.h \
    DartsTableContext/dartstablesectionutility.h \
    DartsTableContext/dartstableslas.h \
    DartsTableContext/dptablemodel.h \
    DartsTableContext/dstablemodel.h \
    DartsTableContext/idartstablesectionutility.h \
    DartsTableContext/igetdatafromdatacontext.h \
    DartsTableContext/iqmldatabuilder.h \
    DartsTableContext/itableindicevalues.h \
    DartsModelsContext/LocalDartsModelsContext/DbServices/loadfromstorage.h \
    DartsModelsContext/LocalDartsModelsContext/DbServices/savetostorage.h \
    DartsModelsContext/LocalDartsModelsContext/IndexesDbServices/dartsindex.h \
    DartsModelsContext/LocalDartsModelsContext/IndexesServices/dartsindexbuilder.h \
    DartsModelsContext/LocalDartsModelsContext/Injectors/dartsindexinjector.h \
    DartsModelsContext/LocalDartsModelsContext/Injectors/dartsinputinjector.h \
    DartsModelsContext/LocalDartsModelsContext/Injectors/dartsplayerinjector.h \
    DartsModelsContext/LocalDartsModelsContext/Injectors/dartstournamentinjector.h \
    DartsModelsContext/LocalDartsModelsContext/Injectors/injectdartsroutines.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/countdartsinputs.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinput.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputbuilder.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputconverter.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputdb.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputstobytearray.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/getdartsinputs.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/removedartsinputs.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputs.h \
    DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputsbyindexes.h \
    DartsModelsContext/LocalDartsModelsContext/PlayerServices/dartsconvertplayer.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/addtournamenttodb.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartsaddinputtodb.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartsdisplayplayerinput.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartshideplayerinput.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartsinputtojson.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartsresettournament.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/dartstournamentrepair.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentasjson.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentsasjson.h \
    DartsModelsContext/LocalDartsModelsContext/Routines/removetournamentsfromdb.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsbuilder.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsjsonconverter.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsmetamodelbuilder.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartssetwinner.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsverifyconsistency.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartwinnermodelbuilder.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentfromdb.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentids.h \
    DartsModelsContext/LocalDartsModelsContext/TournamentsDbServices/dartsdbcontext.h \
    DartsModelsContext/LocalDartsModelsContext/localdartsmodelscontext.h \
    PlayerModelsContext/Contracts/ContextSLA/abstractplayercontext.h \
    PlayerModelsContext/Contracts/DataSLAs/ijsonbuilder.h \
    PlayerModelsContext/Contracts/DbSLAs/IPlayersDbContext.h \
    PlayerModelsContext/Contracts/DbSLAs/PlayersDbSLAs.h \
    PlayerModelsContext/Contracts/DbSLAs/ifetchdb.h \
    PlayerModelsContext/Contracts/DbSLAs/igetplayerfromdb.h \
    PlayerModelsContext/Contracts/DbSLAs/iplayer.h \
    PlayerModelsContext/Contracts/DbSLAs/iplayerbuilder.h \
    PlayerModelsContext/Contracts/DbSLAs/isaveplayers.h \
    PlayerModelsContext/Contracts/IOSLAs/ifiledataio.h \
    PlayerModelsContext/Contracts/ModelsSLAs/iduplicatechecker.h \
    PlayerModelsContext/PlayerContextWithJson/CreatePlayerContext/playerscontext.h \
    PlayerModelsContext/PlayerContextWithJson/DataServices/plajsonbuilder.h \
    PlayerModelsContext/PlayerContextWithJson/DbServices/isaveplayers.h \
    PlayerModelsContext/PlayerContextWithJson/DbServices/loadplayermodels.h \
    PlayerModelsContext/PlayerContextWithJson/DbServices/playersdbcontext.h \
    PlayerModelsContext/PlayerContextWithJson/DbServices/saveplayermodels.h \
    PlayerModelsContext/PlayerContextWithJson/ModelsServices/duplicatechecker.h \
    PlayerModelsContext/PlayerContextWithJson/Services/getplayersfromdb.h \
    PlayerModelsContext/PlayerContextWithJson/Services/plabuilder.h \
    PlayerModelsContext/PlayerContextWithJson/Services/playermodel.h \
    PlayerModelsContext/PlayerContextWithJson/CreatePlayerContext/createplayerscontext.h \
    QmlContext/qmlpropertiesbuilder.h \
    QmlContext/registerqmldartstabletypes.h \
    QmlContext/registerqmlsingletons.h \
    QmlContext/registerqmltableutils.h \
    QmlContext/registerqmltypes.h \
    QmlContext/setupqmlcontext.h \
    Shared/filejsonio.h

DISTFILES += \
    Ressources/arrow.png \
    Ressources/checkmark.png \
    Ressources/dartpic.jpg \
    Ressources/dartpic.png \
    Ressources/darttournamentmod.png \
    Ressources/fck.png \
    Ressources/fck_jersey_logo.png \
    Ressources/hitler.png \
    Ressources/pngfuel.com.png \
    Ressources/s12_1.jpg \
    Ressources/skull.png \
    Ressources/tuborgclassic.png \
    Ressources/users.png \
    qml/BoardDelegateContentRect.qml \
    qml/BoxedRect.qml \
    qml/ButtonsComponent.qml \
    qml/CRUDButton.qml \
    qml/ComboBoxComponent.qml \
    qml/ConfirmActionBack.qml \
    qml/ConfirmActionButtons.qml \
    qml/ConfirmActionPopUp.qml \
    qml/Content.qml \
    qml/ControllerPlayerDisplay.qml \
    qml/CreatePlayerContent.qml \
    qml/CreateTournamentContent.qml \
    qml/DPCBoard.qml \
    qml/DPCContent.qml \
    qml/DPSCKeyPad.qml \
    qml/DSCBoard.qml \
    qml/DSCContent.qml \
    qml/DSSCBoardFonts.qml \
    qml/DSSCKeyPad.qml \
    qml/DSSCKeyPadInterface.qml \
    qml/DSSCTableFonts.qml \
    qml/DartsMetaValues.qml \
    qml/DartsScoreBoard.qml \
    qml/DartsStatsView.qml \
    qml/DartsTournamentSelectors.qml \
    qml/DataModelContext.qml \
    qml/DecoratedItem.qml \
    qml/DefaultComboBox.qml \
    qml/DefaultPlayerListView.qml \
    qml/DefaultSpinBox.qml \
    qml/DefaultTextInputBox.qml \
    qml/DefaultTitleComponent.qml \
    qml/DefaultTournamentListView.qml \
    qml/HorizontalHeader.qml \
    qml/InteractiveObject.qml \
    qml/ItemBody.qml \
    qml/ItemDelegateInterface.qml \
    qml/ItemListView.qml \
    qml/KeyDataDisplay.qml \
    qml/KeyPadInterface.qml \
    qml/KeyPadItem.qml \
    qml/KeyPadScoreView.qml \
    qml/KeyPadTextView.qml \
    qml/LabelComponent.qml \
    qml/ListViewDelegate.qml \
    qml/LoadingItem.qml \
    qml/LoginComponent.qml \
    qml/MainComponent.qml \
    qml/ManagePageContent.qml \
    qml/MyLabel.qml \
    qml/MyRectangle.qml \
    qml/NavigationView.qml \
    qml/NotificationItem.qml \
    qml/Page.qml \
    qml/PageIconItem.qml \
    qml/PageInterface.qml \
    qml/PageLabelItem.qml \
    qml/PageTopBar.qml \
    qml/PlayerListView.qml \
    qml/PlayerViewDelegate.qml \
    qml/PushButton.qml \
    qml/PushButtonInterface.qml \
    qml/ScaleTransition.qml \
    qml/ScoreBoard.qml \
    qml/ScoreBoardDelegate.qml \
    qml/ScoreBoardHHeader.qml \
    qml/ScoreBoardInterface.qml \
    qml/ScoreBoardTableView.qml \
    qml/ScoreBoardVHeader.qml \
    qml/SpinBoxInputContent.qml \
    qml/StartButtonsInterface.qml \
    qml/StartButtonsView.qml \
    qml/StartMenuButton.qml \
    qml/StartPageContent.qml \
    qml/TextInputBox.qml \
    qml/TextRect.qml \
    qml/ThemeContext.qml \
    qml/TournamentContext.qml \
    qml/TournamentListView.qml \
    qml/TournamentPageContent.qml \
    qml/TournamentPageListView.qml \
    qml/TournamentViewDelegate.qml \
    qml/TurnController.qml \
    qml/TurnControllerInterface.qml \
    qml/UserInputComponent.qml \
    qml/UserInputContent.qml \
    qml/VerticalHeader.qml \
    qml/ViewDelegate.qml \
    qml/createPlayerScripts.js \
    qml/createTournamentScripts.js \
    qml/dartsSelectorsScripts.js \
    qml/dpcBoardDelegateScripts.js \
    qml/dpcBoardHeaderScripts.js \
    qml/dpcboardgeometry.js \
    qml/dpcboardscripts.js \
    qml/dpccontrollerinterface.js \
    qml/dpcinit.js \
    qml/dpcscripts.js \
    qml/dpcupdatecomponents.js \
    qml/dpscKeyPadFactory.js \
    qml/dpscKeyPadScripts.js \
    qml/dpscstatescripts.js \
    qml/dsccontrollerinterface.js \
    qml/dscctrlscripts.js \
    qml/dscinit.js \
    qml/dscstatescripts.js \
    qml/dsscKeyPadFactory.js \
    qml/dsscKeyPadScripts.js \
    qml/dsscboardscripts.js \
    qml/ftpScoreBoardFactory.js \
    qml/horizontalHeaderScripts.js \
    qml/jsPopUpBuilder.js \
    qml/listViewDelegateScripts.js \
    qml/main.qml \
    qml/managePageScripts.js \
    qml/pageScripts.js \
    qml/playerListViewScripts.js \
    qml/pushbuttonScripts.js \
    qml/scoreViewScripts.js \
    qml/scoreboardscripts.js \
    qml/tournamentListViewScripts.js \
    qml/tournamentPageScripts.js \
    qml/updatedsccontext.js
