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
    DartsController/Controller/dartsctrl.cpp \
    DartsController/DCFinishesServices/dcfinishbuilder.cpp \
    DartsController/DCJsonServices/dcjsonbuilder.cpp \
    DartsModelsContext/InputServices/dartsinputstojson.cpp \
    DartsModelsContext/InputServices/dartsiptsdbctx.cpp \
    DartsModelsContext/Services/dartscontext.cpp \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.cpp \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.cpp \
    PlayerModelsContext/DbServices/playersdbcontext.cpp \
    DartsController/DCFinishesServices/dartscreatefinishes.cpp \
    PlayerModelsContext/Services/playerbuilder.cpp \
    PlayerModelsContext/playerscontext.cpp \
    dartstabledatacontext.cpp \
    DartsTableContext/dartstablemodel.cpp \
    NetworkManagerContext/iurlparser.cpp \
    DartsTableContext/dartstableslas.cpp \
    main/main.cpp \
    NetworkManagerContext/networkmanager.cpp \
    Tests/tst_Dart2020.cpp \
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
    AsyncUtils/runlater.h \
    DartsController/Controller/dartsctrl.h \
    DartsController/ControllerSLA/abstractdartsctrl.h \
    DartsController/ControllerSLA/ctrlslas.h \
    DartsController/DCFinishesSLAs/idcfinishbuilder.h \
    DartsController/DCFinishesServices/dcfinishbuilder.h \
    DartsController/DCIndexSLAs/abstractdcidxctrl.h \
    DartsController/DCIndexSLAs/abstractdcreqidxbuilder.h \
    DartsController/DCIndexSLAs/dcindex.h \
    DartsController/DCIndexServices/dcidxjsonbuilder.h \
    DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h \
    DartsController/DCIndexServices/dcreqidxjsonbuilder.h \
    DartsController/DCIndexServices/dpcreqindexbuilder.h \
    DartsController/DCIndexServices/dscreqindexbuilder.h \
    DartsController/DCInputSLAs/abstractdcinputbuilder.h \
    DartsController/DCInputSLAs/abstractdcinputevaluator.h \
    DartsController/DCInputSLAs/dciptvals.h \
    DartsController/DCInputSLAs/idciptconverter.h \
    DartsController/DCInputServices/dciptconverter.h \
    DartsController/DCMetaSLAs/abstractdcmetabuilder.h \
    DartsController/DCMetaSLAs/idcmetactx.h \
    DartsController/DCMetaServices/dcmeta.h \
    DartsController/DCMetaServices/dcmetabuilder.h \
    DartsController/DCMetaServices/dcmetacontext.h \
    DartsController/DCPlayerSLAs/IDCPlayerCtx.h \
    DartsController/DCPlayerServices/dpcplayercontext.h \
    DartsController/DCPlayerServices/dscplayercontroller.h \
    DartsController/DCScoresSLAs/abstractdcscoresctx.h \
    DartsController/DCScoresSLAs/idccalcscore.h \
    DartsController/DCScoresSLAs/idcupdateplayerscores.h \
    DartsController/DCScoresServices/dcscorescontext.h \
    DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h \
    DartsController/DPCServices/DPCTurnValuesBuilder.h \
    DartsController/DPController/createdpc.h \
    DartsController/DSController/createdsc.h \
    DartsController/IndexServices/dpcidxctrl.h \
    DartsController/IndexServices/dscindexcontroller.h \
    DartsController/PlayerStatsSLAs/dcinputstatsslas.h \
    DartsController/PlayerStatsSLAs/dcplayerstat.h \
    DartsController/PlayerStatsSLAs/idccalcmidval.h \
    DartsController/PlayerStatsSLAs/idcgetplayerstat.h \
    DartsController/PlayerStatsSLAs/idcsetinputstats.h \
    DartsController/PlayerStatsSLAs/idcstatscontext.h \
    DartsController/PlayerStatsSLAs/idcupdateplayerstat.h \
    DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h \
    DartsController/DCJsonSLAs/dcjsonbuilderservices.h \
    DartsController/DCJsonSLAs/idcmodeljsonbuilder.h \
    DartsController/DCInputServices/dcinputjsonbuilder.h \
    DartsController/DCJsonServices/dcjsonbuilder.h \
    DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h \
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
    DartsController/StaticInitHelperClass/dcresetcontexts.h \
    DartsControllerBuilder/DCBMetaServices/dcbmeta.h \
    DartsControllerBuilder/Services/createdtsctrl.h \
    DartsModelsContext/DartsPlayersSLAs/itournamentplayers.h \
    DartsModelsContext/DartsPlayersServices/tournamentplayers.h \
    DartsModelsContext/IndexesDbServices/dcidxconverter.h \
    DartsModelsContext/IndexesSLAs/idcidxconverter.h \
    DartsModelsContext/InputModels/diptvals.h \
    DartsModelsContext/InputSLAs/dartsiptslas.h \
    DartsModelsContext/InputServices/countdartsinputs.h \
    DartsModelsContext/InputServices/dartsinputbuilder.h \
    DartsModelsContext/InputServices/dartsinputstojson.h \
    DartsModelsContext/InputServices/dartsiptsdbctx.h \
    DartsModelsContext/InputServices/getdartsinputs.h \
    DartsModelsContext/InputServices/removedartsinputs.h \
    DartsModelsContext/InputServices/sortdartsinputs.h \
    DartsModelsContext/InputServices/sortdartsinputsbyindexes.h \
    DartsModelsContext/IndexesSLAs/dartsindexslas.h \
    DartsModelsContext/InputModelsSLAs/abstractdartsinput.h \
    DartsModelsContext/InputsDbSLAs/DartsiptDbSLAs.h \
    DartsModelsContext/InputsDbSLAs/igetinputs.h \
    DartsModelsContext/InputsDbSLAs/iremovedartsinputs.h \
    DartsModelsContext/SLAs/DartsModelsSLAs.h \
    DartsModelsContext/SLAs/abstractdtsctx.h \
    DartsModelsContext/Services/createdartscontext.h \
    DartsModelsContext/Services/dartscontext.h \
    DartsModelsContext/TournamentModels/dartsmetamodel.h \
    DartsModelsContext/TournamentServices/GetDartsTournamentIds.h \
    DartsModelsContext/TournamentServices/dartsbuilder.h \
    DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h \
    DartsModelsContext/TournamentServices/dartstournamentrepair.h \
    DartsModelsContext/TournamentServices/dartsverifyconsistency.h \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h \
    DartsModelsContext/TournamentServices/resetdartstournament.h \
    DartsModelsContext/IndexesDbSLAs/idartsindex.h \
    DartsModelsContext/IndexesDbServices/dartsindex.h \
    DartsModelsContext/IndexesSLAs/iupdatedartsindexes.h \
    DartsModelsContext/IndexesServices/updatedartsindexes.h \
    DartsModelsContext/InputModels/dartsinputstats.h \
    DartsModelsContext/InputModelsSLAs/idartsinputstats.h \
    DartsModelsContext/TournamentsDbSLAs/dartsdbslas.h \
    DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/igetdartstournament.h \
    DartsModelsContext/TournamentModels/dartstournament.h \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.h \
    DartsModelsContext/TournamentsDbServices/dartsjsonbuilder.h \
    DartsModelsContext/TournamentsSLAs/dartsslas.h \
    DartsModelsContext/TournamentsSLAs/idartsconsistency.h \
    DartsModelsContext/TournamentsSLAs/idartsmetamodelbuilder.h \
    DartsModelsContext/TournamentsSLAs/igettournamentids.h \
    DartsModelsContext/TournamentsSLAs/iresetdartstournament.h \
    DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h \
    DartsModelsContext/TournamentsSLAs/itournamentrepair.h \
    DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h \
    DartTournamentsContext/DTCModelsServices/abstracttournament.h \
    DartsController/DCIndexSLAs/dcindexslas.h \
    DartsController/DCInputSLAs/dcinputsslas.h \
    DartsController/DCJsonSLAs/dcjsonslas.h \
    DartsController/DCMetaSLAs/dcmetaslas.h \
    DartsController/DCPlayerSLAs/DCPlayerSLAs.h \
    DartsController/DCScoresSLAs/dcscoreslas.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h \
    DartsController/DCMetaServices/dartsstatuscodes.h \
    DartsController/DCMetaSLAs/idartsstatuscodes.h \
    DartsModelsContext/TournamentsSLAs/idmcaddindexestotournament.h \
    DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h \
    DartsTableContext/TableCellsServices/dartsinitrowvalues.h \
    FileOperationsContext/SLAs/ifiledataio.h \
    FileOperationsContext/Services/filejsonio.h \
    JsonUtils/jsonextractor.h \
    DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h \
    ModelsContext/DbSLAs/abstractloadfromstorage.h \
    ModelsContext/DbSLAs/icreatedatafrom.h \
    ModelsContext/DbSLAs/icreatemodelsfrom.h \
    ModelsContext/DbSLAs/ipersistmemdb.h \
    ModelsContext/DbServices/loadfromstorage.h \
    ModelsContext/DbServices/persistdbctx.h \
    ModelsContext/ModelsContextSLAs/abstractmdsctx.h \
    PlayerModelsContext/DbSLAs/IPlayersDbContext.h \
    PlayerModelsContext/DbSLAs/PlayersDbSLAs.h \
    PlayerModelsContext/DbSLAs/iplayerbuilder.h \
    PlayerModelsContext/DbSLAs/iplayerjsonbuilder.h \
    PlayerModelsContext/DbServices/playersdbcontext.h \
    PlayerModelsContext/SLAs/abstractplayerscontext.h \
    PlayerModelsContext/Services/playerbuilder.h \
    PlayerModelsContext/Services/playerjsonbuilder.h \
    PlayerModelsContext/createplayerscontext.h \
    PlayerModelsContext/playerscontext.h \
    QmlContext/qmlpropertiesbuilder.h \
    DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h \
    Tests/SignalSpyManager.h \
    Tests/TestJsonDartsBuilder.h \
    Tests/TestJsonPlayerBuilder.h \
    createqmlvariants.h \
    DartsController/DCFinishesServices/dartsboundaries.h \
    DartsController/DCFinishesSLAs/dartsconstructslas.h \
    DartsController/DCFinishesServices/dartscreatefinishes.h \
    DartsController/DCFinishesServices/dartscreateterminalthreshold.h \
    dartsdatacontextitemutility.h \
    DartsController/DCFinishesServices/dartsdefaultattempts.h \
    DartsController/DCFinishesServices/dartsdivisors.h \
    DartsController/DCFinishesServices/dartsfieldvalues.h \
    DartsModelsContext/InputServices/dartsinput.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
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
    DartsModelsContext/InputSLAs/icountinputmodels.h \
    DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h \
    DartsController/DCFinishesSLAs/idartsattemptsservice.h \
    DartsController/DCFinishesSLAs/idartsboundaries.h \
    DartsController/DCFinishesSLAs/idartscreatefinishes.h \
    DartsController/DCFinishesSLAs/idartscreateterminalthreshold.h \
    DartsController/DCFinishesSLAs/idartsdivisorvalues.h \
    DartsController/DCFinishesSLAs/idartsfieldvalues.h \
    DartsController/DCFinishesSLAs/idartsfinishesdb.h \
    DartsController/DCFinishesSLAs/idartsmodidentifiers.h \
    DartsTableContext/dstablemodel.h \
    DartsTableContext/DataContextSLAs/idartstabledatacontext.h \
    idartstablesectionutility.h \
    DartsController/DCFinishesSLAs/idartsterminaldivisor.h \
    DartsController/DCFinishesSLAs/idartsthresholdvalues.h \
    ModelsContext/DbSLAs/idbcontext.h \
    igetdatafromdatacontext.h \
    PlayerModelsContext/DbSLAs/igetplayerfromdb.h \
    ModelsContext/DbSLAs/imodelsdbcontext.h \
    ModelsContext/PredicateSLAs/imodelpredicate.h \
    iqmldatabuilder.h \
    DartsModelsContext/InputSLAs/isortinputmodels.h \
    DartsTableContext/TableSectionsSLAs/itablecellcontext.h \
    itableindicevalues.h \
    DartsTableContext/TableSectionsSLAs/itablesectioncontext.h \
    DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h \
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
    NetworkManagerContext/networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    NetworkManagerContext/replytimeout.h \
    registerqmltypes.h \
    setupqmlcontext.h \
    testconfiguration.h \
    NetworkManagerContext/urlparser.h \
    testeventloop.h
DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
