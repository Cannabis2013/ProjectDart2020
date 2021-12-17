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
    DartsController/Controller/dartscontroller.cpp \
    DartsController/DCFinishesServices/dcfinishbuilder.cpp \
    DartsController/DCJsonServices/dcjsonbuilder.cpp \
    DartsModelsContext/InputServices/dartsinputstojson.cpp \
    DartsModelsContext/Services/dartscontext.cpp \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.cpp \
    DartsController/DCFinishesServices/dartscreatefinishes.cpp \
    PlayerModelsContext/Services/plabuilder.cpp \
    DartsTableContext/dartstabledatacontext.cpp \
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
    DartControllerContext/SLAs/absgamectrl.h \
    DartsController/Controller/dartscontroller.h \
    DartsController/ControllerSLA/absdartsctrl.h \
    DartsController/ControllerSLA/ctrlslas.h \
    DartsController/DCFinishesSLAs/idcfinishbuilder.h \
    DartsController/DCFinishesServices/dcfinishbuilder.h \
    DartsController/DCIndexSLAs/dcindex.h \
    DartsController/DCIndexSLAs/idcidxctrl.h \
    DartsController/DCIndexServices/dcidxjsonbuilder.h \
    DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h \
    DartsController/DCIndexServices/dcreqidxjsonbuilder.h \
    DartsController/DCInputSLAs/abstractdcinputbuilder.h \
    DartsController/DCInputSLAs/abstractdciptconverter.h \
    DartsController/DCInputSLAs/dcinput.h \
    DartsController/DCInputSLAs/idcipteval.h \
    DartsController/DCInputServices/dciptconverter.h \
    DartsController/DCMetaSLAs/abstractdcmetabuilder.h \
    DartsController/DCMetaSLAs/idcmetacontext.h \
    DartsController/DCMetaServices/dcmeta.h \
    DartsController/DCMetaServices/dcmetabuilder.h \
    DartsController/DCMetaServices/dcmetacontext.h \
    DartsController/DCScoresSLAs/absdccalcscore.h \
    DartsController/DCScoresSLAs/absdcplayersctx.h \
    DartsController/DCScoresSLAs/absdcupdscoresdetails.h \
    DartsController/DCScoresSLAs/dcplayerscoresslas.h \
    DartsController/DCScoresServices/dcupdplastats.h \
    DartsController/DCScoresServices/dpcplayerscontext.h \
    DartsController/DCScoresServices/dscplayerscontext.h \
    DartsController/DCTurnValuesSLAs/abstractdcturnvalues.h \
    DartsController/DPCServices/DPCTurnValuesBuilder.h \
    DartsController/DPController/createdpc.h \
    DartsController/DSCServices/dsccalcscore.h \
    DartsController/DSController/createdsc.h \
    DartsModelsContext//TournamentModels/tnmvalues.h \
    DartsController/IndexServices/dpcidxctrl.h \
    DartsController/IndexServices/dscindexcontroller.h \
    DartsController/ModelsComCtxSLAs/abstractdcaddtomdsctx.h \
    DartsController/ModelsComCtxServices/dcaddtomodelcontext.h \
    DartsController/PlayerStatsSLAs/absdcsetiptstats.h \
    DartsController/PlayerStatsSLAs/dcinputstatsslas.h \
    DartsController/PlayerStatsSLAs/dcplayerstats.h \
    DartsController/PlayerStatsSLAs/idcgetplayerstat.h \
    DartsController/PlayerStatsSLAs/idcstatscontext.h \
    DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h \
    DartsController/DCJsonSLAs/dcjsonbuilderservices.h \
    DartsController/DCJsonSLAs/idcmodeljsonbuilder.h \
    DartsController/DCInputServices/dcinputjsonbuilder.h \
    DartsController/DCJsonServices/dcjsonbuilder.h \
    DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h \
    DartsController/DCMetaServices/dcsettournamentid.h \
    DartsController/DCScoresServices/dcscorejsonbuilder.h \
    DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h \
    DartsController/DPCServices/dpcinputbuilder.h \
    DartsController/DPCServices/dpcinputevaluator.h \
    DartsController/DSCServices/dscinputbuilder.h \
    DartsController/DSCServices/dscinputevaluator.h \
    DartsController/PlayerStatsServices/dcstatscontext.h \
    DartsController/PlayerStatsServices/dpcupdatescorerange.h \
    DartsController/PlayerStatsServices/dscupdscorerng.h \
    DartsController/StaticInitHelperClass/dcinit.h \
    DartsControllerBuilder/Services/createdtsctrl.h \
    DartsModelsContext/DbSLAs/iconverttomodels.h \
    DartsModelsContext/IndexesDbServices/dcidxconverter.h \
    DartsModelsContext/IndexesSLAs/idartsidxbuilder.h \
    DartsModelsContext/IndexesSLAs/idcidxbuilder.h \
    DartsModelsContext/IndexesServices/dartsidxbuilder.h \
    DartsModelsContext/InputModels/diptvals.h \
    DartsModelsContext/InputSLAs/dartsiptslas.h \
    DartsModelsContext/InputSLAs/icreatemodelvalues.h \
    DartsModelsContext/InputServices/countdartsinputs.h \
    DartsModelsContext/InputServices/createdartsinputvalues.h \
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
    DartsModelsContext/SLAs/absdartsctx.h \
    DartsModelsContext/Services/createdartscontext.h \
    DartsModelsContext/Services/dartscontext.h \
    DartsModelsContext/TournamentModels/dartsmetamodel.h \
    DartsModelsContext/TournamentModelsSLAs/idartstournament.h \
    DartsModelsContext/TournamentServices/GetDartsTournamentIds.h \
    DartsModelsContext/TournamentServices/dartsbuilder.h \
    DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h \
    DartsModelsContext/TournamentServices/dartstournamentrepair.h \
    DartsModelsContext/TournamentServices/dartsverifyconsistency.h \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h \
    DartsModelsContext/TournamentServices/jsontodartsmodels.h \
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
    DartsModelsContext/TournamentsSLAs/idartscreatemeta.h \
    DartsModelsContext/TournamentsSLAs/igettournamentids.h \
    DartsModelsContext/TournamentsSLAs/iresetdartstournament.h \
    DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h \
    DartsModelsContext/TournamentsSLAs/itournamentrepair.h \
    DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/TournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h \
    DartsController/DCIndexSLAs/dcindexslas.h \
    DartsController/DCInputSLAs/dcinputsslas.h \
    DartsController/DCJsonSLAs/dcjsonslas.h \
    DartsController/DCMetaSLAs/dcmetaslas.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h \
    DartsModelsContext/TournamentsSLAs/idmcaddindexestotournament.h \
    DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h \
    DartsTableContext/TableCellsServices/dartsinitrowvalues.h \
    FileOperationsContext/SLAs/ifiledataio.h \
    FileOperationsContext/Services/filejsonio.h \
    DartsModelsContext/DbSLAs/abstractloadmodels.h \
    DartsModelsContext/DbSLAs/abstractsavetostorage.h \
    DartsModelsContext/DbSLAs/imodelconverter.h \
    DartsModelsContext/DbServices/loadfromstorage.h \
    DartsModelsContext/DbServices/persistdbctx.h \
    PlayerModelsContext/DataSLAs/idatabuilder.h \
    PlayerModelsContext/DataServices/plajsonbuilder.h \
    PlayerModelsContext/DbSLAs/IPlayersDbContext.h \
    PlayerModelsContext/DbSLAs/PlayersDbSLAs.h \
    PlayerModelsContext/DbSLAs/ifetchdb.h \
    PlayerModelsContext/DbSLAs/iplayer.h \
    PlayerModelsContext/DbSLAs/iplayerbuilder.h \
    PlayerModelsContext/DbServices/isaveplayers.h \
    PlayerModelsContext/DbServices/loadplayermodels.h \
    PlayerModelsContext/DbServices/playersdbcontext.h \
    PlayerModelsContext/DbServices/saveplayermodels.h \
    PlayerModelsContext/ModelsSLAs/iduplicatechecker.h \
    PlayerModelsContext/ModelsServices/duplicatechecker.h \
    PlayerModelsContext/SLAs/absplactx.h \
    PlayerModelsContext/Services/plabuilder.h \
    PlayerModelsContext/createplayerscontext.h \
    PlayerModelsContext/playerscontext.h \
    QmlContext/qmlpropertiesbuilder.h \
    Tests/SignalSpyManager.h \
    Tests/tst_createplayers.h \
    Tests/tst_dartstournaments.h \
    Tests/tst_dpcontroller.h \
    Tests/tst_dscontroller.h \
    DartsTableContext/createqmlvariants.h \
    DartsController/DCFinishesServices/dartsboundaries.h \
    DartsController/DCFinishesSLAs/dartsconstructslas.h \
    DartsController/DCFinishesServices/dartscreatefinishes.h \
    DartsController/DCFinishesServices/dartscreateterminalthreshold.h \
    DartsTableContext/dartsdatacontextitemutility.h \
    DartsController/DCFinishesServices/dartsdefaultattempts.h \
    DartsController/DCFinishesServices/dartsdivisors.h \
    DartsController/DCFinishesServices/dartsfieldvalues.h \
    DartsModelsContext/InputServices/dartsinput.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
    DartsTableContext/QMLDartsDataModel/dartsplayerdatamodel.h \
    DartsTableContext/dartstablecellcontext.h \
    DartsTableContext/dartstablecreatecolumnindices.h \
    DartsTableContext/dartstablecreatecolumns.h \
    DartsTableContext/dartstablecreaterowindices.h \
    DartsTableContext/dartstabledatacontext.h \
    DartsTableContext/dartstabledimensions.h \
    DartsTableContext/dartstablemodel.h \
    DartsTableContext/dartstablesectionmanipulator.h \
    DartsTableContext/dartstablesectionutility.h \
    DartsController/DCFinishesServices/dartsterminaldivisor.h \
    DartsController/DCFinishesServices/dartsthreshold.h \
    DartsController/DCFinishesServices/dccreatefinishes.h \
    DartsController/DCFinishesServices/dclogisticdb.h \
    DartsController/DCScoresServices//dcscoremodel.h \
    DartsController/DCTurnValuesServices/dcturnvalues.h \
    DartsController/DSCServices/dscvaluesbuilder.h \
    DartsTableContext/dartstableslas.h \
    DartsTableContext/dptablemodel.h \
    DartsModelsContext/TournamentServices/getdartstournamentfromdb.h \
    PlayerModelsContext/Services/getplayersfromdb.h \
    DartsController/DPCServices/getscorefromdpcinput.h \
    DartsTableContext/FontMetrics/greatestheight.h \
    DartsTableContext/FontMetrics/greatestwidth.h \
    DartsModelsContext/InputSLAs/icountinputmodels.h \
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
    DartsTableContext/idartstablesectionutility.h \
    DartsController/DCFinishesSLAs/idartsterminaldivisor.h \
    DartsController/DCFinishesSLAs/idartsthresholdvalues.h \
    DartsModelsContext//DbSLAs/idbcontext.h \
    DartsTableContext/igetdatafromdatacontext.h \
    PlayerModelsContext/DbSLAs/igetplayerfromdb.h \
    DartsModelsContext/PredicateSLAs/imodelpredicate.h \
    DartsTableContext/iqmldatabuilder.h \
    DartsModelsContext/InputSLAs/isortinputmodels.h \
    DartsTableContext/TableSectionsSLAs/itablecellcontext.h \
    DartsTableContext/itableindicevalues.h \
    DartsTableContext/TableSectionsSLAs/itablesectioncontext.h \
    DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h \
    DartsModelsContext/ModelSLAs/imodel.h \
    DartsModelsContext/InputModelsSLAs/iplayerinput.h \
    NetworkManagerContext/iurlparser.h \
    DartsTableContext/LinkedList/linkedlist.h \
    DartsTableContext/QMLTableMetrics/mhtablecolumnwidth.h \
    DartsTableContext/QMLTableMetrics/mhtablerowheight.h \
    DartsTableContext/FontMetrics/mhtablesectionmetrics.h \
    NetworkManagerContext/networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    SetupQmlApp/registerqmldartstabletypes.h \
    SetupQmlApp/registerqmlsingletons.h \
    SetupQmlApp/registerqmltableutils.h \
    NetworkManagerContext/replytimeout.h \
    SetupQmlApp/registerqmltypes.h \
    SetupQmlApp/setupqmlcontext.h \
    Tests/testconfiguration.h \
    NetworkManagerContext/urlparser.h
DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
