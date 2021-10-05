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
    DartsModelsContext/DMCInputSLAs/dmcinputslas.cpp \
    DartsModelsContext/DMCTournamentSLAs/dartstournamentslas.cpp \
    DartsModelsContext/DMCTournamentServices/adddetailstotournamentjson.cpp \
    DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.cpp \
    DartsController/DCConnectServices/connectdartscontroller.cpp \
    DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.cpp \
    DartsControllerBuilder/Services/createdartscontroller.cpp \
    DartsModelsContext/DMCInputServices/createdartspointsfromjson.cpp \
    PlayerModelsContext/Services/createplayersfromjson.cpp \
    DartApplication/Services/dartapplication.cpp \
    DartsController/Controller/dartscontroller.cpp \
    DartApplication/SLAs/dartapplicationslas.cpp \
    DartsController/DCFinishesServices/dartscreatefinishes.cpp \
    dartsdbcreatejsonfrominputs.cpp \
    DartsModelsContext/Services/dartsmodelscontext.cpp \
    DartsModelsContext/Services/dartsjsonmodelscontext.cpp \
    dartspmcdatacontext.cpp \
    dartsroundindexbyattempt.cpp \
    dartstablemodel.cpp \
    dartstableservices.cpp \
    DartsController/DCFinishesServices/dcinputfinishes.cpp \
    DartsControllerBuilder/DCBMetaServices/dcmeta.cpp \
    DartsController/DCScoresSLAs/dcscoreservices.cpp \
    DartsController/DCMetaServices/dcwinnerservice.cpp \
    DartsController/DPCServices/dpcindexcontroller.cpp \
    DartsController/DSCServices/dscindexcontroller.cpp \
    DartsModelsContext/DMCTournamentServices/extractwinnerinfofromjson.cpp \
    DartsModelsContext/DMCInputServices/dmcinputjsondb.cpp \
    PlayerModelsContext/Services/getplayersfromdb.cpp \
    iurlparser.cpp \
    PlayerModelsContext/DbServices/jsonplayersdbcontext.cpp \
    main/main.cpp \
    networkmanager.cpp \
    PlayerModelsContext/playermodelscontext.cpp \
    PlayerModelsContext/SLAs/playermodelsslas.cpp \
    DartApplication/RouteServices/routebydisplayhint.cpp \
    DartTournamentsContext/DTCDbServices/tournamentsjsondb.cpp \
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
    DartsController/DCInputSLAs/abstractevaluatedcinput.h \
    DartsController/DCJsonSLAs/icreatejsonobject.h \
    DartsController/DCJsonSLAs/idccreatebytearray.h \
    DartsController/DCJsonServices/dccreatebytearray.h \
    DartsController/DCJsonServices/dccreateemptyjsonobject.h \
    DartsController/DCMetaSLAs/idcstatus.h \
    DartsController/DCTurnValuesSLAs/iDCTurnValJsonKeys.h \
    DartsController/DCTurnValuesServices/dcturnvaljsonkeys.h \
    DartsModelsContext/DMCIndexesSLAs/IDCIndexesJsonKeys.h \
    DartsModelsContext/DMCIndexesSLAs/dartsindexesslas.h \
    DartsModelsContext/DMCIndexesSLAs/idartsindexes.h \
    DartsModelsContext/DMCIndexesServices/dartsindexes.h \
    DartsModelsContext/DMCIndexesServices/dindexesjsonkeys.h \
    DartsModelsContext/DMCInputSLAs/dmcinputslas.h \
    DartsModelsContext/DMCInputSLAs/igetdartsinputfromdb.h \
    DartsModelsContext/DMCTournamentSLAs/dartstournamentslas.h \
    DartsController/DCInputSLAs/IDCInputKeyCodes.h \
    DartsController/DCInputSLAs/idccreateinputmodels.h \
    DartsController/DCInputSLAs/idcinputjsonkeys.h \
    DartsController/DCInputServices/DCInputKeyCodes.h \
    DartsController/DCScoresSLAs/idccreatecandidatemodels.h \
    DartsController/DCScoresSLAs/idcgetscore.h \
    DartsController/DCInputSLAs/dcinputsservices.h \
    DartsController/DPCServices/CreateDPCTurnValues.h \
    DartsController/DCPlayerSLAs/DCPlayerServices.h \
    DartsController/DCInputServices/dccreateinputmodels.h \
    DartsController/DPCServices/dpccreateinputmodel.h \
    DartsController/DCMetaServices/dchint.h \
    DartsController/DCInputServices/dcinputjsonkeys.h \
    DartsController/DCMetaServices/dctournamentid.h \
    DartsController/DCMetaServices/dartsstatuscodes.h \
    DartsController/DCMetaServices/dcmetastatus.h \
    DartsController/DCMetaSLAs/idartsdeterminestatusbyid.h \
    DartsController/DCMetaSLAs/idartsstatuscodes.h \
    DartsController/DCMetaSLAs/idchint.h \
    DartsController/DCMetaSLAs/dcmetaservices.h \
    DartsController/DCMetaSLAs/idctournamentid.h \
    ModelsContext/MCDbSLAs/iremovemodelfromdb.h \
    DartsModelsContext/SLAs/abstractdartsmodelscontext.h \
    DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h \
    DartsControllerBuilder/SLAs/abstractdcbuilder.h \
    DartApplication/RouteSLAs/abstractroutebydisplayhint.h \
    DartApplication/RouteSLAs/abstractroutebygamemode.h \
    DartsModelsContext/DMCTournamentServices/adddetailstotournamentjson.h \
    DartsModelsContext/DMCTournamentServices/addplayerdetailstotournament.h \
    DartsController/DCJsonServices/addplayernamestodartsinputsasjson.h \
    DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.h \
    applicationbuilder.h \
    DartsModelsContext/DMCTournamentServices/createdartstournamentsfromjson.h \
    DartsController/DCConnectServices/connectdartscontroller.h \
    DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.h \
    PlayerModelsContext/PMCConnectServices/connectplayerscontext.h \
    DartApplication/ConnectServices/connectservices.h \
    ServicesProviderContext/SPConnectServices/connectservicesprovider.h \
    DartsControllerBuilder/DCBMetaServices/createDCMetaInfo.h \
    DartsControllerBuilder/Services/createdartscontroller.h \
    DartsModelsContext/DMCTournamentServices/createdartstournamentfromjson.h \
    DartApplication/ConnectRouteServices/connectroutebydisplayhint.h \
    DartApplication/ConnectRouteServices/connectroutebygamemode.h \
    DartsModelsContext/DMCInputServices/createdartspointsfromjson.h \
    DartsModelsContext/DMCTournamentServices/createjsonfromdartstournaments.h \
    DartsController/DCPlayerServices/createjsonfromdcplayer.h \
    createjsonfromdp.h \
    PlayerModelsContext/Services/createjsonfromplayermodels.h \
    PlayerModelsContext/Services/createjsonfromplayers.h \
    DartsModelsContext/DMCTournamentServices/createjsonfromtournamentdetails.h \
    PlayerModelsContext/Services/createplayerfromjson.h \
    PlayerModelsContext/Services/createplayermodels.h \
    PlayerModelsContext/Services/createplayersfromjson.h \
    createqmlvariants.h \
    DartsController/DCFinishesServices/dartsboundaries.h \
    DartsController/Controller/dartscontroller.h \
    DartsController/DCFinishesSLAs/dartsconstructslas.h \
    DartApplication/SLAs/dartapplicationslas.h \
    DartsController/DCFinishesServices/dartscreatefinishes.h \
    DartsModelsContext/DMCTournamentServices/dartscreatejsonmetadata.h \
    DartsController/DCFinishesServices/dartscreateterminalthreshold.h \
    createscorevaluefromdi.h \
    dartsdatacontextitemutility.h \
    dartsdatamodelpoint.h \
    dartsdbcreatejsonfrominputs.h \
    dartsdbcreatejsonfrominputs.h \
    DartsController/DCFinishesServices/dartsdefaultattempts.h \
    DartsController/DCFinishesServices/dartsdivisors.h \
    DartsController/DCFinishesServices/dartsfieldvalues.h \
    DartsModelsContext/DMCInputServices/dartsinput.h \
    DartsModelsContext/DMCInputServices/dartsinputsjsondb.h \
    DartsModelsContext/Services/dartsmodelscontext.h \
    DartsModelsContext/Services/dartsjsonmodelscontext.h \
    DartsController/DCFinishesServices/dartsmodidentifiers.h \
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
    DartsModelsContext/DMCTournamentServices/dartstournamentextractor.h \
    DartsModelsContext/DMCTournamentServices/dartstournamentjsonbuilder.h \
    DartsModelsContext/DMCDbServices/dartstournamentsjsondb.h \
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
    DartsController/DCIndexSLAs/dcindexservices.h \
    DartsController/DCIndexServices/dcindexundo.h \
    DartsController/DCIndexServices/dcinitializeindexservice.h \
    DartsController/DCMetaServices/dcinitialscore.h \
    DartsController/DCFinishesServices/dcinputfinishes.h \
    DartsController/DCInputServices/dcinputmodel.h \
    DartsController/DCJsonSLAs/dcjsonservices.h \
    DartsController/DCFinishesServices/dclogisticdb.h \
    DartsControllerBuilder/DCBMetaServices/dcmeta.h \
    DartsController/DCPlayerServices/dcplayer.h \
    DartsController/DCPlayerServices/dcplayerbuilder.h \
    DartsController/DCPlayerServices/dcplayerkeys.h \
    DartsController/DCPlayerServices/dcplayerservice.h \
    DartsController/DCIndexServices/dcresetindexes.h \
    DartsController/DCScoresServices/dcresetscoremodels.h \
    DartsController/DCScoresServices//dcscoremodel.h \
    DartsController/DCScoresSLAs/dcscoreservices.h \
    DartsController/DCScoresServices/dcscoresservice.h \
    DartsController/DCScoresServices/dcsubtractscore.h \
    DartsController/DCTurnValuesServices/dcturnvalues.h \
    DartsController/DCTurnValuesSLAs/dcturnvaluesservices.h \
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
    DartsModelsContext/DMCInputServices/dmcinputstojson.h \
    DartsModelsContext/DMCInputServices/dmccountinputs.h \
    DartsModelsContext/DMCInputServices/dmccreateinput.h \
    DartsModelsContext/DMCInputServices/dmcgetinputfromdb.h \
    DartsModelsContext/DMCInputServices/dmcgetinputmodels.h \
    DartsModelsContext/DMCInputServices/dmcinputjsondb.h \
    DartsModelsContext/DMCInputServices/dmcinputtojson.h \
    DartsModelsContext/DMCInputServices/dmcremoveinputsfromdb.h \
    DartsModelsContext/DMCInputServices/dmcsetinputhint.h \
    DartsModelsContext/DMCInputServices/dmcsortinputs.h \
    DartsModelsContext/DMCIndexesServices/dmccreateindexes.h \
    DartsModelsContext/DMCIndexesServices/dmcindexestojson.h \
    DartsModelsContext/DMCUtilsSLAs/dmcutilsslas.h \
    dpmctablemodel.h \
    dpsctablemodel.h \
    DartsController/DSCServices/dsccreateinputmodel.h \
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
    DartsModelsContext/DMCTournamentServices/gettournamentwinner.h \
    greatestheight.h \
    greatestwidth.h \
    DartsModelsContext/DMCTournamentSLAs/iadddetailstotournamentjson.h \
    iaddplayerdetailstomodel.h \
    DartsModelsContext/DMCTournamentServices/addplayerdetailstotournament.h \
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
    icreatefromjson.h \
    DartsController/DCPlayerSLAs/icreatejsonfromdcplayer.h \
    ModelsContext/MCJsonSLAs/icreatejsonfrommodels.h \
    PlayerModelsContext/SLAs/icreatejsonfromplayers.h \
    DartsModelsContext/DMCTournamentSLAs/icreatejsonfromtournamentdetails.h \
    ModelsContext/MCJsonSLAs/icreatemodelsfromjson.h \
    PlayerModelsContext/SLAs/icreateplayerfromjson.h \
    PlayerModelsContext/SLAs/icreateplayermodels.h \
    DartsController/DCFinishesSLAs/idartsattemptsservice.h \
    DartsController/DCFinishesSLAs/idartsboundaries.h \
    idartscontrollerjsonservice.h \
    DartsController/DCFinishesSLAs/idartscreatefinishes.h \
    DartsModelsContext/DMCIndexesSLAs/idartscreateindexes.h \
    DartsModelsContext/DMCInputSLAs/idartscreateinput.h \
    DartsModelsContext/DMCInputSLAs/idartscreatejsonfrommodel.h \
    DartsModelsContext/DMCTournamentSLAs/idartscreatejsonmetadata.h \
    DartsController/DCFinishesSLAs/idartscreateterminalthreshold.h \
    DartsController/DCFinishesSLAs/idartsdivisorvalues.h \
    DartsController/DCFinishesSLAs/idartsfieldvalues.h \
    DartsController/DCFinishesSLAs/idartsfinishesdb.h \
    DartsModelsContext/DMCIndexesSLAs/idartsindexestojson.h \
    DartsController/DCFinishesSLAs/idartsinputfinishes.h \
    DartsModelsContext//DMCInputSLAs/idartsinputmodelstojson.h \
    DartsModelsContext/DMCInputSLAs/idartsinputsethint.h \
    DartsController/DCInputSLAs/idartsinputstojson.h \
    DartsController/DCFinishesSLAs/idartsmodidentifiers.h \
    idartsplayermodelbuilderservice.h \
    idartstabledatacontext.h \
    idartstablesectionutility.h \
    DartsController/DCFinishesSLAs/idartsterminaldivisor.h \
    DartsController/DCFinishesSLAs/idartsthresholdvalues.h \
    DartsModelsContext/DMCTournamentSLAs/idartstournamentextractor.h \
    DartsModelsContext/DMCTournamentSLAs/idartstournamentjsonbuilder.h \
    idatamodelpoint.h \
    idatamodeltablecellsizes.h \
    ModelsContext/MCDbSLAs/idbcontext.h \
    DartsController/DCScoresSLAs/idcaddscore.h \
    DartsController/DCInputSLAs/idccreateinputmodel.h \
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
    DartsController/DCInputSLAs/idcinputstojson.h \
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
    DartsModelsContext/DMCTournamentSLAs/iextractwinnerinfo.h \
    FileOperationsContext/SLAs/ifilereader.h \
    FileOperationsContext/SLAs/ifilewriter.h \
    DartsModelsContext/DMCTournamentSLAs/igetdartstournamentfromdb.h \
    igetdatafromdatacontext.h \
    DartsModelsContext/DMCInputSLAs/igetinputmodelsservice.h \
    PlayerModelsContext/SLAs/igetplayerfromdb.h \
    DartsModelsContext/DMCTournamentSLAs/igettournamentwinner.h \
    iheaderlabels.h \
    DartsModelsContext/DMCTournamentSLAs/ijsontodartstournamentmodel.h \
    DartsController/DCJsonSLAs/ijsonvaluesextractor.h \
    ModelsContext/MCDbSLAs/imodelsdbcontext.h \
    PlayerModelsContext/SLAs/iplayermodelscontext.h \
    ModelsContext/MCPredicateSLAs/imodelpredicate.h \
    iqmldatabuilder.h \
    DartsModelsContext/DMCInputSLAs/iremovedartsinputsfromdb.h \
    ModelsContext/MCDbSLAs/iremovemodelsfromdb.h \
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
    DartsModelsContext/DMCInputSLAs/idartsinput.h \
    idatacontext.h \
    ModelsContext/MCModelsSLAs/imodel.h \
    DartsModelsContext/DMCInputSLAs/iplayerinput.h \
    PlayerModelsContext/SLAs/iplayermodel.h \
    DartTournamentsContext/DTCModelsSLAs/itournament.h \
    itournamentparameter.h \
    iurlparser.h \
    PlayerModelsContext/DbServices/jsonplayersdbcontext.h \
    jsonvaluesextractor.h \
    linkedlist.h \
    DartApplication/Services/localdartapplication.h \
    PlayerModelsContext/localplayerscontext.h \
    PlayerModelsContext/DbServices/localplayersdbcontext.h \
    mhtablecolumnwidth.h \
    mhtablerowheight.h \
    mhtablesectionmetrics.h \
    modelsdbioservices.h \
    ModelsContext/MCJsonSLAs/modelsdbjsonslas.h \
    networkmanager.h \
    PlayerModelsContext/Services/playermodel.h \
    PlayerModelsContext/playermodelscontext.h \
    PlayerModelsContext/SLAs/playermodelsslas.h \
    FileOperationsContext/Services/readbytearray.h \
    registercustomtypes.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    removemodelsfromdb.h \
    replytimeout.h \
    DartApplication/RouteServices/routebydisplayhint.h \
    DartApplication/RouteServices/routebytournamentgamemode.h \
    DartApplication/RouteServices/routeservicesprovider.h \
    setupqmlcontext.h \
    sortdartspointinputsbyindexes.h \
    testconfiguration.h \
    DartTournamentsContext/DTCModelsServices/tournament.h \
    DartTournamentsContext/DTCDbServices/tournamentsjsondb.h \
    urlparser.h \
    testeventloop.h \
    verticalstringlabels.h \
    FileOperationsContext/Services/writebytearray.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
