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
    DartApplication/RouteServices/routebyinputhint.cpp \
    DartsController/DCJsonServices/dcjsonbuilder.cpp \
    DartsController/DPController/dpcontroller.cpp \
    DartsController/DartsScoreController/dscontroller.cpp \
    DartsControllerBuilder/Services/dcbuilder.cpp \
    DartsModelsContext/InputServices/dartsinputbuilder.cpp \
    DartsModelsContext/TournamentServices/dartwinnermodelbuilder.cpp \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.cpp \
    DartsController/DCScoresSLAs/dcscoreslas.cpp \
    DartsModelsContext/InputServices/dartsinputsdbcontext.cpp \
    DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.cpp \
    DartsController/DCConnectServices/connectdartscontroller.cpp \
    DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.cpp \
    PlayerModelsContext/DbServices/playersdbcontext.cpp \
    PlayerModelsContext/Services/createplayersfromjson.cpp \
    DartApplication/Services/dartapplication.cpp \
    DartsController/Controller/dartscontroller.cpp \
    DartApplication/SLAs/dartapplicationslas.cpp \
    DartsController/DCFinishesServices/dartscreatefinishes.cpp \
    DartsModelsContext/Services/dartsmodelscontext.cpp \
    DartsModelsContext/Services/dartsjsonmodelscontext.cpp \
    DartsModelsContext/InputServices/dartsinputjsonbuilder.cpp \
    dartsroundindexbyattempt.cpp \
    dartstabledatacontext.cpp \
    dartstablemodel.cpp \
    dartstableservices.cpp \
    DartsController/DCFinishesServices/dcinputfinishes.cpp \
    iurlparser.cpp \
    main/main.cpp \
    networkmanager.cpp \
    PlayerModelsContext/playermodelscontext.cpp \
    tst_Dart2020.cpp \
    urlparser.cpp

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
    DartApplication/ConnectBuilderServices/ConnectDCBuilder.h \
    DartApplication/RouteSLAs/abstractroutebyhint.h \
    DartApplication/RouteServices/routebyinputhint.h \
    DartsController/DCIndexSLAs/idcindexbuilder.h \
    DartsController/DCIndexSLAs/idcindexcontroller.h \
    DartsController/DCIndexSLAs/idcreqinputindexbuilder.h \
    DartsController/DCIndexServices/dcindex.h \
    DartsController/DCIndexServices/dcindexjsonbuilder.h \
    DartsController/DCIndexServices/dcinputindexbuilder.h \
    DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h \
    DartsController/DCIndexServices/dcreqindexjsonbuilder.h \
    DartsController/DCIndexServices/dpcreqindexbuilder.h \
    DartsController/DCIndexServices/dscreqindexbuilder.h \
    DartsController/DCInputSLAs/abstractdcinputevaluator.h \
    DartsController/DCInputSLAs/idcinputbuilder.h \
    DartsController/DCInputServices/dcinput.h \
    DartsController/DCPlayerSLAs/IDCPlayerController.h \
    DartsController/DCPlayerServices/dpcplayercontroller.h \
    DartsController/DCPlayerServices/dscplayercontroller.h \
    DartsController/DCScoresSLAs/idccalcscore.h \
    DartsController/DCScoresSLAs/idcscoremodels.h \
    DartsController/DCScoresSLAs/idcupdateplayerscores.h \
    DartsController/DCScoresServices/dcscoremodels.h \
    DartsController/DPCServices/DPCTurnValuesBuilder.h \
    DartsController/IndexServices/dpcindexcontroller.h \
    DartsController/IndexServices/dscindexcontroller.h \
    DartsController/InitializeServices/dcinitservices.h \
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
    DartsController/DCMetaSLAs/idcmetajsonbuilder.h \
    DartsController/DCMetaSLAs/idcmetamodelbuilder.h \
    DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h \
    DartsController/DCMetaServices/dcmetainfo.h \
    DartsController/DCMetaServices/dcmetajsonbuilder.h \
    DartsController/DCMetaServices/dcmetamodelbuilder.h \
    DartsController/DCMetaServices/dcsettournamentid.h \
    DartsController/DCPlayerSLAs/idcplayerbuilder.h \
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
    DartsControllerBuilder/Services/dcbuilder.h \
    DartsModelsContext/InputSLAs/dartsinputslas.h \
    DartsModelsContext/InputServices/countdartsinputs.h \
    DartsModelsContext/InputServices/dartsinputbuilder.h \
    DartsModelsContext/InputServices/getdartsinputfromdb.h \
    DartsModelsContext/InputServices/getdartsinputmodels.h \
    DartsModelsContext/InputServices/removedartsinputsfromdb.h \
    DartsModelsContext/InputServices/sortdartsinputs.h \
    DartsModelsContext/InputServices/sortdartsinputsbyindexes.h \
    DartsModelsContext/IndexesDbServices/dartsindexbuilder.h \
    DartsModelsContext/IndexesSLAs/dartsindexslas.h \
    DartsModelsContext/IndexesSLAs/idartsindexbuilder.h \
    DartsModelsContext/InputModelsSLAs/abstractdartsinput.h \
    DartsModelsContext/InputsDbSLAs/igetdartsinput.h \
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
    DartsController/DCIndexServices/dcindexesjsonkeys.h \
    DartsController/DCInputSLAs/dcinputsslas.h \
    DartsController/DCJsonSLAs/dcjsonslas.h \
    DartsController/DCMetaSLAs/dcmetaslas.h \
    DartsController/DCMetaSLAs/idcstatus.h \
    DartsController/DCPlayerSLAs/DCPlayerSLAs.h \
    DartsController/DCScoresSLAs/dcscoreslas.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h \
    DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h \
    DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h \
    DartsModelsContext/InputServices/dartsinputsdbcontext.h \
    DartsModelsContext/TournamentsSLAs/dartstournamentslas.h \
    DartsController/DCMetaServices/dchint.h \
    DartsController/DCMetaServices/dctournamentid.h \
    DartsController/DCMetaServices/dartsstatuscodes.h \
    DartsController/DCMetaServices/dcmetastatus.h \
    DartsController/DCMetaSLAs/idartsdeterminestatusbyid.h \
    DartsController/DCMetaSLAs/idartsstatuscodes.h \
    DartsController/DCMetaSLAs/idchint.h \
    DartsController/DCMetaSLAs/idctournamentid.h \
    DartsModelsContext/TournamentsSLAs/idmcaddindexestotournament.h \
    DartsModelsContext/InputsDbSLAs/DartsInputsDbSLAs.h \
    DartsModelsContext/InputsDbSLAs/IDartsInputsDbContext.h \
    DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h \
    ModelsContext/DbSLAs/IDbPersistence.h \
    DartsModelsContext/SLAs/abstractdartsmodelscontext.h \
    DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h \
    DartsControllerBuilder/SLAs/abstractdcbuilder.h \
    DartApplication/RouteSLAs/abstractroutebygamemode.h \
    DartsController/DCJsonServices/addplayernamestodartsinputsasjson.h \
    DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.h \
    PlayerModelsContext/DbSLAs/IPlayersDbContext.h \
    PlayerModelsContext/DbSLAs/PlayersDbSLAs.h \
    PlayerModelsContext/DbServices/playersdbcontext.h \
    PlayerModelsContext/DbSLAs/iplayercontextjsonbuilder.h \
    PlayerModelsContext/DbSLAs/iplayercontextmodelbuilder.h \
    applicationbuilder.h \
    DartsController/DCConnectServices/connectdartscontroller.h \
    DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.h \
    PlayerModelsContext/PMCConnectServices/connectplayerscontext.h \
    DartApplication/ConnectServices/connectservices.h \
    ServicesProviderContext/SPConnectServices/connectservicesprovider.h \
    DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h \
    DartApplication/ConnectRouteServices/connectroutebydisplayhint.h \
    DartApplication/ConnectRouteServices/connectroutebygamemode.h \
    createjsonfromdp.h \
    PlayerModelsContext/Services/createjsonfromplayermodels.h \
    PlayerModelsContext/Services/createplayersfromjson.h \
    createqmlvariants.h \
    DartsController/DCFinishesServices/dartsboundaries.h \
    DartsController/Controller/dartscontroller.h \
    DartsController/DCFinishesSLAs/dartsconstructslas.h \
    DartApplication/SLAs/dartapplicationslas.h \
    DartsController/DCFinishesServices/dartscreatefinishes.h \
    DartsController/DCFinishesServices/dartscreateterminalthreshold.h \
    createscorevaluefromdi.h \
    dartsdatacontextitemutility.h \
    dartsdatamodelpoint.h \
    DartsController/DCFinishesServices/dartsdefaultattempts.h \
    DartsController/DCFinishesServices/dartsdivisors.h \
    DartsController/DCFinishesServices/dartsfieldvalues.h \
    DartsModelsContext/InputServices/dartsinput.h \
    DartsModelsContext/Services/dartsmodelscontext.h \
    DartsModelsContext/Services/dartsjsonmodelscontext.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
    DartsModelsContext/InputServices/dartsinputjsonbuilder.h \
    dartsplayerdatamodel.h \
    dartspscIndexBuilder.h \
    dartsroundindexbyattempt.h \
    dartstablecellcontext.h \
    dartstablecreatecolumnindices.h \
    dartstablecreatecolumns.h \
    dartstablecreaterowindices.h \
    dartstabledatacontext.h \
    dartstabledimensions.h \
    dartstablefillservice.h \
    dartstablemodel.h \
    dartstablesectionmanipulator.h \
    dartstablesectionutility.h \
    dartstableservices.h \
    DartsController/DCFinishesServices/dartsterminaldivisor.h \
    DartsController/DCFinishesServices/dartsthreshold.h \
    DartsController/DCFinishesServices/dccreatefinishes.h \
    DartsController/DCScoresServices/dcgetscorecand.h \
    DartsController/DCScoresServices/dccreatescoremodels.h \
    DartsController/DCMetaServices/dcinitialscore.h \
    DartsController/DCFinishesServices/dcinputfinishes.h \
    DartsController/DCFinishesServices/dclogisticdb.h \
    DartsControllerBuilder/DCBMetaServices/dcmeta.h \
    DartsController/DCPlayerServices/dcplayer.h \
    DartsController/DCPlayerServices/dcplayerbuilder.h \
    DartsController/DCScoresServices//dcscoremodel.h \
    DartsController/DCTurnValuesServices/dcturnvalues.h \
    DartsController/DCScoresServices/dcupdatescoremodels.h \
    DartsController/DCMetaServices/dcwinnerservice.h \
    defaultdartscellcontext.h \
    DartsController/DCMetaServices/determinestatusbyid.h \
    DartsController/DPController/dpcontroller.h \
    dpsctablemodel.h \
    DartsController/DartsScoreController/dscontroller.h \
    DartsController/DSCServices/dscvaluesbuilder.h \
    dssctablemodel.h \
    DartsModelsContext/TournamentServices/getdartstournamentfromdb.h \
    PlayerModelsContext/Services/getplayersfromdb.h \
    DartsController/DPCServices/getscorefromdpcinput.h \
    DartsController/DSCServices/getscorefromdscinput.h \
    greatestheight.h \
    greatestwidth.h \
    DartsController/DCJsonSLAs/iaddplayernamestojson.h \
    DartsController/DCJsonSLAs/iaddtotalscoretodartsinputsjson.h \
    DartControllerContext/ConnectSLAs/iconnectcontroller.h \
    DartsModelsContext/DMCConnectSLAs/iconnectdartsmodelscontext.h \
    PlayerModelsContext/PMCConnectSLAs/iconnectplayermodelscontext.h \
    DartApplication/ConnectBuilderSLAs/iconnectdcbuilder.h \
    DartApplication/ConnectRouteSLAs/iconnectroutebydisplayhint.h \
    DartApplication/ConnectRouteSLAs/iconnectroutebygamemode.h \
    DartApplication/ConnectRouteSLAs/iconnectroutetoapplication.h \
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
    idartsplayermodelbuilderservice.h \
    idartstabledatacontext.h \
    idartstablesectionutility.h \
    DartsController/DCFinishesSLAs/idartsterminaldivisor.h \
    DartsController/DCFinishesSLAs/idartsthresholdvalues.h \
    idatamodelpoint.h \
    idatamodeltablecellsizes.h \
    ModelsContext/DbSLAs/idbcontext.h \
    DartsController/DCScoresSLAs/idcgetscorecand.h \
    DartsController/DCMetaSLAs/idcinitialscore.h \
    DartsController/DCScoresSLAs/idcupdatescoremodels.h \
    DartsController/DCMetaSLAs/idcwinnerservice.h \
    FileOperationsContext/SLAs/ifilereader.h \
    FileOperationsContext/SLAs/ifilewriter.h \
    igetdatafromdatacontext.h \
    DartsModelsContext/InputsDbSLAs/igetinputmodelsservice.h \
    PlayerModelsContext/DbSLAs/igetplayerfromdb.h \
    iheaderlabels.h \
    ModelsContext/DbSLAs/imodelsdbcontext.h \
    PlayerModelsContext/SLAs/iplayermodelscontext.h \
    ModelsContext/MCPredicateSLAs/imodelpredicate.h \
    iqmldatabuilder.h \
    DartsModelsContext/InputsDbSLAs/iremovedartsinputsfromdb.h \
    DartApplication/RouteSLAs/irouteservicesprovider.h \
    DartsModelsContext/InputSLAs/isortinputmodels.h \
    itablecellcontext.h \
    itablecolumnindexbuilder.h \
    itablefillcells.h \
    itableindicevalues.h \
    itablesectioncontext.h \
    itablesectionmanipulator.h \
    DartsController/ControllerSLA/abstractdartscontroller.h \
    DartApplication/SLAs/AbstractApplicationInterface.h \
    DartControllerContext/SLAs/abstractgamecontroller.h \
    DartApplication/Services/dartapplication.h \
    idatacontext.h \
    ModelsContext/MCModelsSLAs/imodel.h \
    DartsModelsContext/InputModelsSLAs/iplayerinput.h \
    PlayerModelsContext/DbSLAs/iplayermodel.h \
    DartTournamentsContext/DTCModelsSLAs/itournament.h \
    itournamentparameter.h \
    iurlparser.h \
    linkedlist.h \
    DartApplication/Services/localdartapplication.h \
    PlayerModelsContext/localplayerscontext.h \
    mhtablecolumnwidth.h \
    mhtablerowheight.h \
    mhtablesectionmetrics.h \
    ModelsContext/DbSLAs/modelsdbioservices.h \
    networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    PlayerModelsContext/playermodelscontext.h \
    FileOperationsContext/Services/readbytearray.h \
    registercustomtypes.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    replytimeout.h \
    DartApplication/RouteServices/routebytournamentgamemode.h \
    DartApplication/RouteServices/routeservicesprovider.h \
    setupqmlcontext.h \
    testconfiguration.h \
    urlparser.h \
    testeventloop.h \
    FileOperationsContext/Services/writebytearray.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
