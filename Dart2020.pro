QT += quick testlib

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DartsController/DCJsonServices/dcjsonbuilder.cpp \
    DartsModelsContext/InputServices/dartsinputbuilder.cpp \
    DartsModelsContext/Services/dartscontext.cpp \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.cpp \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.cpp \
    DartsModelsContext/InputServices/dartsinputsdbcontext.cpp \
    PlayerModelsContext/DbServices/playersdbcontext.cpp \
    PlayerModelsContext/Services/createplayersfromjson.cpp \
    DartsController/Controller/dartscontroller.cpp \
    DartsController/DCFinishesServices/dartscreatefinishes.cpp \
    DartsModelsContext/InputServices/dartsinputjsonbuilder.cpp \
    PlayerModelsContext/playerscontext.cpp \
    dartstabledatacontext.cpp \
    DartsTableContext/dartstablemodel.cpp \
    DartsController/DCFinishesServices/dcinputfinishes.cpp \
    NetworkManagerContext/iurlparser.cpp \
    DartsTableContext/dartstableslas.cpp \
    main/main.cpp \
    NetworkManagerContext/networkmanager.cpp \
    tst_Dart2020.cpp \
    NetworkManagerContext/urlparser.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
                Dart2020_da_DK.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AsyncUtils/runnable.h \
    DartsController/ControllerSLA/controllerslas.h \
    DartsController/DCIndexSLAs/idcindexcontroller.h \
    DartsController/DCIndexSLAs/idcreqinputindexbuilder.h \
    DartsController/DCIndexServices/dcindexjsonbuilder.h \
    DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h \
    DartsController/DCIndexServices/dcreqindexjsonbuilder.h \
    DartsController/DCIndexServices/dpcreqindexbuilder.h \
    DartsController/DCIndexServices/dscreqindexbuilder.h \
    DartsController/DCInputSLAs/abstractdcinputevaluator.h \
    DartsController/DCInputSLAs/idcinputbuilder.h \
    DartsController/DCMetaSLAs/idcmetainfo.h \
    DartsController/DCMetaSLAs/idcmetamodelbuilder.h \
    DartsController/DCMetaServices/dcmeta.h \
    DartsController/DCMetaServices/dcmetainfo.h \
    DartsController/DCPlayerSLAs/IDCPlayerController.h \
    DartsController/DCPlayerServices/dpcplayercontroller.h \
    DartsController/DCPlayerServices/dscplayercontroller.h \
    DartsController/DCScoresSLAs/idccalcscore.h \
    DartsController/DCScoresSLAs/idcscoremodels.h \
    DartsController/DCScoresSLAs/idcupdateplayerscores.h \
    DartsController/DCScoresServices/dcscoremodels.h \
    DartsController/DPCServices/DPCTurnValuesBuilder.h \
    DartsController/DPController/createdpc.h \
    DartsController/DSController/createdsc.h \
    DartsController/IndexServices/dpcindexcontroller.h \
    DartsController/IndexServices/dscindexcontroller.h \
    DartsController/PlayerStatsSLAs/dcinputstatsslas.h \
    DartsController/PlayerStatsSLAs/dcplayerstat.h \
    DartsController/PlayerStatsSLAs/idccalcmidval.h \
    DartsController/PlayerStatsSLAs/idcgetplayerstat.h \
    DartsController/PlayerStatsSLAs/idcplayerstats.h \
    DartsController/PlayerStatsSLAs/idcsetinputstats.h \
    DartsController/PlayerStatsSLAs/idcupdateplayerstat.h \
    DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h \
    DartsController/DCJsonSLAs/dcjsonbuilderservices.h \
    DartsController/DCJsonSLAs/idcmodeljsonbuilder.h \
    DartsController/DCInputServices/dcinputjsonbuilder.h \
    DartsController/DCJsonServices/dcjsonbuilder.h \
    DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h \
    DartsController/DCMetaServices/dcmetamodelbuilder.h \
    DartsController/DCMetaServices/dcsettournamentid.h \
    DartsController/DCScoresSLAs/idcscorebuilder.h \
    DartsController/DCScoresServices/dcscorejsonbuilder.h \
    DartsController/DCScoresServices/dcupdateinputdetails.h \
    DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h \
    DartsController/DPCServices/dpcinputbuilder.h \
    DartsController/DPCServices/dpcinputevaluator.h \
    DartsController/DSCServices/dscinputbuilder.h \
    DartsController/DSCServices/dscinputevaluator.h \
    DartsController/PlayerStatsServices/dcplayerstatsmanager.h \
    DartsController/PlayerStatsServices/dcupdateplayerstat.h \
    DartsController/PlayerStatsServices/dcupdatescorerange.h \
    DartsController/PlayerStatsServices/dpccalcmidval.h \
    DartsController/PlayerStatsServices/dsccalcmidval.h \
    DartsController/StaticInitHelperClass/dcinit.h \
    DartsControllerBuilder/DCBMetaServices/dcbmeta.h \
    DartsControllerBuilder/Services/createdartscontroller.h \
    DartsModelsContext/IndexesDbServices/dcindexbuilder.h \
    DartsModelsContext/IndexesSLAs/idcindexbuilder.h \
    DartsModelsContext/InputSLAs/dartsinputslas.h \
    DartsModelsContext/InputServices/countdartsinputs.h \
    DartsModelsContext/InputServices/dartsinputbuilder.h \
    DartsModelsContext/InputServices/getdartsinputfromdb.h \
    DartsModelsContext/InputServices/getdartsinputmodels.h \
    DartsModelsContext/InputServices/removedartsinputsfromdb.h \
    DartsModelsContext/InputServices/sortdartsinputs.h \
    DartsModelsContext/InputServices/sortdartsinputsbyindexes.h \
    DartsModelsContext/IndexesSLAs/dartsindexslas.h \
    DartsModelsContext/InputModelsSLAs/abstractdartsinput.h \
    DartsModelsContext/InputsDbSLAs/igetdartsinput.h \
    DartsModelsContext/SLAs/abstractdartscontext.h \
    DartsModelsContext/Services/dartscontext.h \
    DartsModelsContext/Services/dartscontextbuilder.h \
    DartsModelsContext/TournamentModels/dartsmetamodel.h \
    DartsModelsContext/TournamentServices/GetDartsTournamentIds.h \
    DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h \
    DartsModelsContext/TournamentServices/resetdartstournament.h \
    DartsModelsContext/IndexesDbSLAs/idartsindex.h \
    DartsModelsContext/IndexesDbServices/dartsindex.h \
    DartsModelsContext/IndexesSLAs/iupdatedartsindexes.h \
    DartsModelsContext/IndexesServices/updatedartsindexes.h \
    DartsModelsContext/InputModels/dartsinputstats.h \
    DartsModelsContext/InputModelsSLAs/idartsinputstats.h \
    DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/igetdartstournament.h \
    DartsModelsContext/TournamentModels/dartstournament.h \
    DartsModelsContext/TournamentsDbServices/dartsjsonbuilder.h \
    DartsModelsContext/TournamentsSLAs/idartsmetamodelbuilder.h \
    DartsModelsContext/TournamentsSLAs/igettournamentids.h \
    DartsModelsContext/TournamentsSLAs/iresetdartstournament.h \
    DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h \
    DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h \
    DartsModelsContext/TournamentServices/dartstournamentbuilder.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h \
    DartsModelsContext/InputsDbSLAs/idartsinputjsonbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.h \
    DartTournamentsContext/DTCModelsServices/abstracttournament.h \
    DartsController/DCIndexSLAs/dcindexslas.h \
    DartsController/DCInputSLAs/dcinputsslas.h \
    DartsController/DCJsonSLAs/dcjsonslas.h \
    DartsController/DCMetaSLAs/dcmetaslas.h \
    DartsController/DCPlayerSLAs/DCPlayerSLAs.h \
    DartsController/DCScoresSLAs/dcscoreslas.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h \
    DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h \
    DartsModelsContext/InputServices/dartsinputsdbcontext.h \
    DartsModelsContext/TournamentsSLAs/dartstournamentslas.h \
    DartsController/DCMetaServices/dartsstatuscodes.h \
    DartsController/DCMetaSLAs/idartsstatuscodes.h \
    DartsModelsContext/TournamentsSLAs/idmcaddindexestotournament.h \
    DartsModelsContext/InputsDbSLAs/DartsInputsDbSLAs.h \
    DartsModelsContext/InputsDbSLAs/IDartsInputsDbContext.h \
    DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h \
    DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h \
    DartsTableContext/TableCellsServices/dartsinitrowvalues.h \
    JsonUtils/jsonbuilder.h \
    JsonUtils/jsonextractor.h \
    ModelsContext/DbSLAs/IDbPersistence.h \
    DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h \
    ModelsContext/ModelsContextSLAs/abstractmodelscontext.h \
    PlayerModelsContext/DbSLAs/IPlayersDbContext.h \
    PlayerModelsContext/DbSLAs/PlayersDbSLAs.h \
    PlayerModelsContext/DbSLAs/iplayerjsonbuilder.h \
    PlayerModelsContext/DbServices/playersdbcontext.h \
    PlayerModelsContext/DbSLAs/iplayercontextmodelbuilder.h \
    PlayerModelsContext/SLAs/abstractplayerscontext.h \
    PlayerModelsContext/PMCConnectServices/connectplayerscontext.h \
    PlayerModelsContext/createplayerscontext.h \
    PlayerModelsContext/playerscontext.h \
    QmlContext/qmlpropertiesbuilder.h \
    ServicesProviderContext/SPConnectServices/connectservicesprovider.h \
    DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h \
    PlayerModelsContext/Services/createjsonfromplayermodels.h \
    PlayerModelsContext/Services/createplayersfromjson.h \
    createqmlvariants.h \
    DartsController/DCFinishesServices/dartsboundaries.h \
    DartsController/Controller/dartscontroller.h \
    DartsController/DCFinishesSLAs/dartsconstructslas.h \
    DartsController/DCFinishesServices/dartscreatefinishes.h \
    DartsController/DCFinishesServices/dartscreateterminalthreshold.h \
    dartsdatacontextitemutility.h \
    DartsController/DCFinishesServices/dartsdefaultattempts.h \
    DartsController/DCFinishesServices/dartsdivisors.h \
    DartsController/DCFinishesServices/dartsfieldvalues.h \
    DartsModelsContext/InputServices/dartsinput.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
    DartsModelsContext/InputServices/dartsinputjsonbuilder.h \
    DartsTableContext/QMLDartsDataModel/dartsplayerdatamodel.h \
    dartstablecellcontext.h \
    dartstablecreatecolumnindices.h \
    dartstablecreatecolumns.h \
    dartstablecreaterowindices.h \
    dartstabledatacontext.h \
    dartstabledimensions.h \
    DartsTableContext/dartstablemodel.h \
    dartstablesectionmanipulator.h \
    dartstablesectionutility.h \
    DartsController/DCFinishesServices/dartsterminaldivisor.h \
    DartsController/DCFinishesServices/dartsthreshold.h \
    DartsController/DCFinishesServices/dccreatefinishes.h \
    DartsController/DCScoresServices/dccreatescoremodels.h \
    DartsController/DCFinishesServices/dcinputfinishes.h \
    DartsController/DCFinishesServices/dclogisticdb.h \
    DartsController/DCScoresServices//dcscoremodel.h \
    DartsController/DCTurnValuesServices/dcturnvalues.h \
    DartsController/DSCServices/dscvaluesbuilder.h \
    DartsTableContext/dartstableslas.h \
    DartsTableContext/dptablemodel.h \
    DartsModelsContext/TournamentServices/getdartstournamentfromdb.h \
    PlayerModelsContext/Services/getplayersfromdb.h \
    DartsController/DPCServices/getscorefromdpcinput.h \
    DartsController/DSCServices/getscorefromdscinput.h \
    DartsTableContext/FontMetrics/greatestheight.h \
    DartsTableContext/FontMetrics/greatestwidth.h \
    ServicesProviderContext/SPConnectSLAs//iconnectservicesprovider.h \
    DartsModelsContext/InputSLAs/icountinputmodels.h \
    DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h \
    DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h \
    DartsController/DCFinishesSLAs/idartsattemptsservice.h \
    DartsController/DCFinishesSLAs/idartsboundaries.h \
    DartsController/DCFinishesSLAs/idartscreatefinishes.h \
    DartsController/DCFinishesSLAs/idartscreateterminalthreshold.h \
    DartsController/DCFinishesSLAs/idartsdivisorvalues.h \
    DartsController/DCFinishesSLAs/idartsfieldvalues.h \
    DartsController/DCFinishesSLAs/idartsfinishesdb.h \
    DartsController/DCFinishesSLAs/idartsinputfinishes.h \
    DartsController/DCFinishesSLAs/idartsmodidentifiers.h \
    DartsTableContext/dstablemodel.h \
    DartsTableContext/DataContextSLAs/idartstabledatacontext.h \
    idartstablesectionutility.h \
    DartsController/DCFinishesSLAs/idartsterminaldivisor.h \
    DartsController/DCFinishesSLAs/idartsthresholdvalues.h \
    ModelsContext/DbSLAs/idbcontext.h \
    FileOperationsContext/SLAs/ifilereader.h \
    FileOperationsContext/SLAs/ifilewriter.h \
    igetdatafromdatacontext.h \
    DartsModelsContext/InputsDbSLAs/igetinputmodelsservice.h \
    PlayerModelsContext/DbSLAs/igetplayerfromdb.h \
    ModelsContext/DbSLAs/imodelsdbcontext.h \
    ModelsContext/PredicateSLAs/imodelpredicate.h \
    iqmldatabuilder.h \
    DartsModelsContext/InputsDbSLAs/iremovedartsinputsfromdb.h \
    DartsModelsContext/InputSLAs/isortinputmodels.h \
    DartsTableContext/TableSectionsSLAs/itablecellcontext.h \
    itableindicevalues.h \
    DartsTableContext/TableSectionsSLAs/itablesectioncontext.h \
    DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h \
    DartsController/ControllerSLA/abstractdartscontroller.h \
    DartControllerContext/SLAs/abstractgamecontroller.h \
    ModelsContext/ModelsSLAs/imodel.h \
    DartsModelsContext/InputModelsSLAs/iplayerinput.h \
    PlayerModelsContext/DbSLAs/iplayermodel.h \
    DartTournamentsContext/DTCModelsSLAs/itournament.h \
    NetworkManagerContext/iurlparser.h \
    DartsTableContext/LinkedList/linkedlist.h \
    DartsTableContext/QMLTableMetrics/mhtablecolumnwidth.h \
    DartsTableContext/QMLTableMetrics/mhtablerowheight.h \
    DartsTableContext/FontMetrics/mhtablesectionmetrics.h \
    ModelsContext/DbSLAs/modelsdbioservices.h \
    NetworkManagerContext/networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    FileOperationsContext/Services/readbytearray.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    NetworkManagerContext/replytimeout.h \
    registerqmltypes.h \
    setupqmlcontext.h \
    testconfiguration.h \
    NetworkManagerContext/urlparser.h \
    testeventloop.h \
    FileOperationsContext/Services/writebytearray.h
DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
