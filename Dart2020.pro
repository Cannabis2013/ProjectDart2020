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
    DartsControllerBuilder/Services/dcbuilder.cpp \
    DartsModelsContext/DMCInputServices/dartsinputbuilder.cpp \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.cpp \
    DartsController/DCScoresSLAs/dcscoreslas.cpp \
    DartsModelsContext/DMCInputServices/dartsinputsdbcontext.cpp \
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
    dartsinputjsonbuilder.cpp \
    dartspmcdatacontext.cpp \
    dartsroundindexbyattempt.cpp \
    dartstablemodel.cpp \
    dartstableservices.cpp \
    DartsController/DCFinishesServices/dcinputfinishes.cpp \
    DartsControllerBuilder/DCBMetaServices/dcmeta.cpp \
    DartsController/DCMetaServices/dcwinnerservice.cpp \
    DartsController/DPCServices/dpcindexcontroller.cpp \
    DartsController/DSCServices/dscindexcontroller.cpp \
    DartsModelsContext/DMCTournamentServices/extractwinnerinfofromjson.cpp \
    iurlparser.cpp \
    main/main.cpp \
    networkmanager.cpp \
    PlayerModelsContext/playermodelscontext.cpp \
    DartApplication/RouteServices/routebydisplayhint.cpp \
    tst_Dart2020.cpp \
    urlparser.cpp \
    verticalstringlabels.cpp

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
    DartsController/DCInputSLAs/idcinputbuilder.h \
    DartsController/DCInputSLAs/idcsetinputjsonvalues.h \
    DartsController/DCMetaSLAs/idcmetajsonbuilder.h \
    DartsController/DCMetaServices/dcmetajsonbuilder.h \
    DartsController/DCMetaServices/dcsettournamentid.h \
    DartsController/DCPlayerSLAs/IDCPlayerAllowancesContext.h \
    DartsController/DCPlayerSLAs/idcplayerjsonbuilder.h \
    DartsController/DCPlayerServices/DPCPlayerAllowancesContext.h \
    DartsController/DCPlayerServices/dcplayerjsonbuilder.h \
    DartsController/DPCServices/dpcinputbuilder.h \
    DartsController/DSCServices/dscinputbuilder.h \
    DartsControllerBuilder/Services/dcbuilder.h \
    DartsModelsContext/DMCInputSLAs/dartsinputslas.h \
    DartsModelsContext/DMCInputServices/countdartsinputs.h \
    DartsModelsContext/DMCInputServices/dartsinputbuilder.h \
    DartsModelsContext/DMCInputServices/getdartsinputfromdb.h \
    DartsModelsContext/DMCInputServices/getdartsinputmodels.h \
    DartsModelsContext/DMCInputServices/removedartsinputsfromdb.h \
    DartsModelsContext/DMCInputServices/sortdartsinputs.h \
    DartsModelsContext/DMCInputServices/sortdartsinputsbyindexes.h \
    DartsModelsContext/DMCTournamentServices/GetDartsTournamentIds.h \
    DartsModelsContext/DMCTournamentServices/dartsmetamodelbuilder.h \
    DartsModelsContext/IndexesDbSLAs/iremovedartsindexes.h \
    DartsModelsContext/IndexesDbServices/dartsindexesbuilder.h \
    DartsModelsContext/IndexesDbServices/getdartsindexesmodel.h \
    DartsModelsContext/IndexesDbServices/removedartsindexes.h \
    DartsModelsContext/IndexesSLAs/dartsindexesslas.h \
    DartsModelsContext/IndexesSLAs/iupdatedartsindexes.h \
    DartsModelsContext/IndexesServices/dartsindexesjsonbuilder.h \
    DartsModelsContext/IndexesServices/updatedartsindexes.h \
    DartsModelsContext/TournamentsSLAs/idartsmetamodelbuilder.h \
    DartsModelsContext/TournamentsSLAs/igettournamentids.h \
    DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h \
    DartsModelsContext/TournamentsSLAs/iwinnerinfobuilder.h \
    DartsModelsContext/DMCTournamentServices/dartstournamentbuilder.h \
    DartsModelsContext/DMCTournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/DMCTournamentServices/setdartsplayerdetails.h \
    DartsModelsContext/IndexesDbSLAs/idartsindexesjsonbuilder.h \
    DartsModelsContext/IndexesDbSLAs/igetdartsindexesmodel.h \
    DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h \
    DartsModelsContext/InputsDbSLAs/idartsinputjsonbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/idartstournamentbuilder.h \
    DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h \
    DartsModelsContext/TournamentsDbServices/dartsdbcontext.h \
    DartTournamentsContext/DTCModelsServices/abstracttournament.h \
    DartsController/DCIndexSLAs/dcindexslas.h \
    DartsController/DCIndexServices/dcindexesjsonkeys.h \
    DartsController/DCInputSLAs/abstractevaluatedcinput.h \
    DartsController/DCInputSLAs/dcinputsslas.h \
    DartsController/DCInputStatsSLAs/DCInputStatsSLAs.h \
    DartsController/DCInputStatsSLAs/idcaveragecalc.h \
    DartsController/DCInputStatsSLAs/idcinputavgjsonkeys.h \
    DartsController/DCInputStatsServices/dcaveragecalc.h \
    DartsController/DCInputStatsServices/dcinputstatsavgkeys.h \
    DartsController/DCJsonSLAs/dcjsonslas.h \
    DartsController/DCJsonSLAs/icreatejsonobject.h \
    DartsController/DCJsonSLAs/idccreatebytearray.h \
    DartsController/DCJsonServices/dccreatebytearray.h \
    DartsController/DCJsonServices/dccreateemptyjsonobject.h \
    DartsController/DCMetaSLAs/dcmetaslas.h \
    DartsController/DCMetaSLAs/idcstatus.h \
    DartsController/DCPlayerSLAs/DCPlayerSLAs.h \
    DartsController/DCScoresSLAs/dcscoreslas.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesslas.h \
    DartsController/DCTurnValuesSLAs/iDCTurnValJsonKeys.h \
    DartsController/DCTurnValuesServices/dcturnvaljsonkeys.h \
    DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h \
    DartsModelsContext/TournamentsDbSLAs/dartstournamentdbslas.h \
    DartsModelsContext/IndexesDbSLAs/dartsindexesdbslas.h \
    DartsModelsContext/IndexesDbSLAs/icreatedartsinexesmodels.h \
    DartsModelsContext/IndexesDbSLAs/idartsindexes.h \
    DartsModelsContext/IndexesDbSLAs/idartsindexesdbcontext.h \
    DartsModelsContext/IndexesDbServices/dartsindexes.h \
    DartsModelsContext/IndexesDbServices/dartsindexesdbcontext.h \
    DartsModelsContext/DMCInputServices/dartsinputsdbcontext.h \
    DartsModelsContext/InputsDbSLAs/igetdartsinputfromdb.h \
    DartsModelsContext/TournamentsSLAs/dartstournamentslas.h \
    DartsController/DCInputSLAs/IDCInputKeyCodes.h \
    DartsController/DCInputServices/DCInputKeyCodes.h \
    DartsController/DCScoresSLAs/idccreatecandidatemodels.h \
    DartsController/DCScoresSLAs/idcgetscore.h \
    DartsController/DPCServices/CreateDPCTurnValues.h \
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
    DartsModelsContext/TournamentsDbServices/dartstournamentjsonbuilder.h \
    ModelsContext/MCDbSLAs/IDbPersistence.h \
    DartsModelsContext/SLAs/abstractdartsmodelscontext.h \
    DartsModelsContext/TournamentsSLAs/abstractdartstournament.h \
    DartsControllerBuilder/SLAs/abstractdcbuilder.h \
    DartApplication/RouteSLAs/abstractroutebydisplayhint.h \
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
    DartsModelsContext/DMCInputServices/dartsinput.h \
    DartsModelsContext/Services/dartsmodelscontext.h \
    DartsModelsContext/Services/dartsjsonmodelscontext.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
    dartsinputjsonbuilder.h \
    dartsinputjsonbuilder.h \
    dartspmccolumnindexbuilder.h \
    dartspmcdatacontext.h \
    dartspmcsectionutility.h \
    dartspscIndexBuilder.h \
    dartsroundindexbyattempt.h \
    dartstablecellcontext.h \
    dartstablecreatecolumnindices.h \
    dartstablecreatecolumns.h \
    dartstablecreaterowindices.h \
    dartstabledimensions.h \
    dartstablefillservice.h \
    dartstablemodel.h \
    dartstablesectionmanipulator.h \
    dartstableservices.h \
    DartsController/DCFinishesServices/dartsterminaldivisor.h \
    DartsController/DCFinishesServices/dartsthreshold.h \
    DartsController/DCScoresServices/dcaddscore.h \
    DartsController/DCFinishesServices/dccreatefinishes.h \
    DartsController/DCScoresServices/dccreatecandidatemodels.h \
    DartsController/DCPlayerServices/dccreateplayersfromjson.h \
    DartsController/DCScoresServices/dcgetscorecand.h \
    DartsController/DCScoresServices/dccreatescoremodels.h \
    DartsController/DCPlayerServices/dcgetwinnermodelfromjson.h \
    DartsController/DCIndexServices/dcindexes.h \
    DartsController/DCIndexServices/dcindexesbuilder.h \
    DartsController/DCIndexServices/dcindexiterator.h \
    DartsController/DCIndexServices/dcindexredo.h \
    DartsController/DCIndexServices/dcindexundo.h \
    DartsController/DCIndexServices/dcinitializeindexservice.h \
    DartsController/DCMetaServices/dcinitialscore.h \
    DartsController/DCFinishesServices/dcinputfinishes.h \
    DartsController/DCInputServices/dcinputmodel.h \
    DartsController/DCFinishesServices/dclogisticdb.h \
    DartsControllerBuilder/DCBMetaServices/dcmeta.h \
    DartsController/DCPlayerServices/dcplayer.h \
    DartsController/DCPlayerServices/dcplayerbuilder.h \
    DartsController/DCPlayerServices/dcplayerkeys.h \
    DartsController/DCPlayerServices/dcplayerservice.h \
    DartsController/DCIndexServices/dcresetindexes.h \
    DartsController/DCScoresServices/dcresetscoremodels.h \
    DartsController/DCScoresServices//dcscoremodel.h \
    DartsController/DCScoresServices/dcscoresservice.h \
    DartsController/DCScoresServices/dcsubtractscore.h \
    DartsController/DCTurnValuesServices/dcturnvalues.h \
    DartsController/DCTurnValuesServices/dcturnvaluestojson.h \
    DartsController/DCScoresServices/dcupdatescoremodels.h \
    DartsController/DCPlayerServices/dcwinnerkeys.h \
    DartsController/DCMetaServices/dcwinnerservice.h \
    defaultdartscellcontext.h \
    DartsController/DCMetaServices/determinestatusbyid.h \
    DartsController/DPCServices/dpcindexcontroller.h \
    DartsController/DPCServices/dpcindexestojson.h \
    DartsController/DPCServices/dpcinputstojson.h \
    DartsController/DPCServices/dpcinputvalidator.h \
    DartsController/DPController/dpcontroller.h \
    dpmctablemodel.h \
    dpsctablemodel.h \
    DartsController/DSCServices/dscindexcontroller.h \
    DartsController/DSCServices/dscindexestojson.h \
    DartsController/DSCServices/dscinputtojson.h \
    DartsController/DSCServices/dscinputvalidator.h \
    DartsController/DartsScoreController/dscontroller.h \
    DartsController/DSCServices/dscvaluesbuilder.h \
    dssctablemodel.h \
    DartsModelsContext/DMCTournamentServices/extractwinnerinfofromjson.h \
    DartsModelsContext/DMCTournamentServices/getdartstournamentfromdb.h \
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
    DartsModelsContext/DMCInputSLAs/icountinputmodels.h \
    DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h \
    DartsController/DCTurnValuesSLAs/icreatedcturnvalues.h \
    DartsController/DCFinishesSLAs/idartsattemptsservice.h \
    DartsController/DCFinishesSLAs/idartsboundaries.h \
    idartscontrollerjsonservice.h \
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
    ModelsContext/MCDbSLAs/idbcontext.h \
    DartsController/DCScoresSLAs/idcaddscore.h \
    DartsController/DCPlayerSLAs/idccreateplayersfromjson.h \
    DartsController/DCScoresSLAs/idccreatescoretuples.h \
    DartsController/DCPlayerSLAs/idcgetplayerscore.h \
    DartsController/DCScoresSLAs/idcgetscorecand.h \
    DartsController/DCPlayerSLAs/idcgetwinnermodelfromjson.h \
    DartsController/DCIndexSLAs/idcindexes.h \
    DartsController/DCIndexSLAs/idcindexesbuilder.h \
    DartsController/DCIndexSLAs/idcindexestojson.h \
    DartsController/DCIndexSLAs/idcindexiterator.h \
    DartsController/DCIndexSLAs/idcindexredo.h \
    DartsController/DCIndexSLAs/idcindexservice.h \
    DartsController/DCIndexSLAs/idcinitializeindexes.h \
    DartsController/DCMetaSLAs/idcinitialscore.h \
    DartsController/DCInputSLAs/idcinputmodel.h \
    DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h \
    DartsController/DCPlayerSLAs/idcplayer.h \
    DartsController/DCPlayerSLAs/idcplayermodelbuilder.h \
    DartsController/DCPlayerSLAs/idcplayerservice.h \
    DartsController/DCIndexSLAs/idcresetindexes.h \
    DartsController/DCScoresSLAs/idcresetscorescoremodels.h \
    DartsController/DCScoresSLAs/idcscoresservice.h \
    DartsController/DCScoresSLAs/idcsubtractscore.h \
    DartsController/DCPlayerSLAs/idcplayerkeys.h \
    DartsController/DCTurnValuesSLAs/idcturnvaluestojson.h \
    DartsController/DCIndexSLAs/idcundoindex.h \
    DartsController/DCScoresSLAs/idcupdatescoremodels.h \
    DartsController/DCMetaSLAs/idcwinnerservice.h \
    FileOperationsContext/SLAs/ifilereader.h \
    FileOperationsContext/SLAs/ifilewriter.h \
    DartsModelsContext/TournamentsDbSLAs/igetdartstournamentfromdb.h \
    igetdatafromdatacontext.h \
    DartsModelsContext/InputsDbSLAs/igetinputmodelsservice.h \
    PlayerModelsContext/DbSLAs/igetplayerfromdb.h \
    iheaderlabels.h \
    ModelsContext/MCDbSLAs/imodelsdbcontext.h \
    PlayerModelsContext/SLAs/iplayermodelscontext.h \
    ModelsContext/MCPredicateSLAs/imodelpredicate.h \
    iqmldatabuilder.h \
    DartsModelsContext/InputsDbSLAs/iremovedartsinputsfromdb.h \
    DartApplication/RouteSLAs/irouteservicesprovider.h \
    DartsController/DCScoresSLAs/iscoresservice.h \
    DartsModelsContext/DMCInputSLAs/isortinputmodels.h \
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
    DartsModelsContext/InputsDbSLAs/idartsinput.h \
    idatacontext.h \
    ModelsContext/MCModelsSLAs/imodel.h \
    DartsModelsContext/InputsDbSLAs/iplayerinput.h \
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
    modelsdbioservices.h \
    networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    PlayerModelsContext/playermodelscontext.h \
    FileOperationsContext/Services/readbytearray.h \
    registercustomtypes.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    replytimeout.h \
    DartApplication/RouteServices/routebydisplayhint.h \
    DartApplication/RouteServices/routebytournamentgamemode.h \
    DartApplication/RouteServices/routeservicesprovider.h \
    setupqmlcontext.h \
    testconfiguration.h \
    urlparser.h \
    testeventloop.h \
    verticalstringlabels.h \
    FileOperationsContext/Services/writebytearray.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
