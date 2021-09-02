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
    adddetailstotournamentjson.cpp \
    addtotalscoretodartspointsjson.cpp \
    connectdartscontroller.cpp \
    connectdartsmodelscontext.cpp \
    createdartspointsfromjson.cpp \
    createjsonfromplayermodels.cpp \
    createplayersfromjson.cpp \
    dartapplication.cpp \
    dartapplicationservices.cpp \
    dartscontroller.cpp \
    dartscontrollerpointmodelsservice.cpp \
    dartscreatepointindexes.cpp \
    dartsdbcreatejsonfrompoints.cpp \
    dartsinputjsondb.cpp \
    dartsinputservices.cpp \
    dartsmodelsservice.cpp \
    dartspmcdatacontext.cpp \
    dartspointsethint.cpp \
    dartspointsjsonservice.cpp \
    dartspointstringsuggestion.cpp \
    dartsroundindexbyattempt.cpp \
    dartssingleattemptinputrowsuggestion.cpp \
    dartstablemodel.cpp \
    dartstableservices.cpp \
    dartstournamentservices.cpp \
    dartsutilityservices.cpp \
    dcbuilder.cpp \
    dcindexcontroller.cpp \
    dcmetainfo.cpp \
    dcwinnerservice.cpp \
    extractwinnerinfofromjson.cpp \
    getinputmodelsservice.cpp \
    getplayersfromdb.cpp \
    iurlparser.cpp \
    jsonmodelsservice.cpp \
    jsonplayersdbcontext.cpp \
    main.cpp \
    networkmanager.cpp \
    playermodelscontext.cpp \
    playermodelsservices.cpp \
    removeinputsfromdb.cpp \
    removemodelsfromdb.cpp \
    routebydisplayhint.cpp \
    routedartsbyinputhint.cpp \
    tournamentsjsondb.cpp \
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
    ConnectDCBuilder.h \
    CreateDPCTurnValues.h \
    GenereicJsonBuilder.h \
    GetScoreFromDCPointModel.h \
    IConnect.h \
    abstractdartsmodelscontext.h \
    abstractdartstournament.h \
    abstractdcbuilder.h \
    abstractroutebydisplayhint.h \
    abstractroutebygamemode.h \
    abstractroutebyinputhint.h \
    adddetailstotournamentjson.h \
    addplayerdetailstotournament.h \
    addplayernamestodartspointsjson.h \
    addtotalscoretodartspointsjson.h \
    applicationbuilder.h \
    connectdartscontroller.h \
    connectdartsmodelscontext.h \
    connectplayerscontext.h \
    connectservices.h \
    connectservicesprovider.h \
    createDCMetaInfo.h \
    createdartstournamentfromjson.h \
    createjsonfromdartspointindexes.h \
    comparedartspointmodels.h \
    connectroutebydisplayhint.h \
    connectroutebygamemode.h \
    connectroutebyinputhint.h \
    createdartspointsfromjson.h \
    createdartstournamentsfromjson.h \
    createjsonfromdartstournaments.h \
    createjsonfromdcplayer.h \
    createjsonfromdp.h \
    createjsonfromdscmodels.h \
    createjsonfromplayermodels.h \
    createjsonfromplayers.h \
    createjsonfromtournamentdetails.h \
    createplayerfromjson.h \
    createplayermodels.h \
    createplayersfromjson.h \
    createqmlvariants.h \
    dartapplicationservices.h \
    dartsaddscore.h \
    dartscontroller.h \
    dartscontrollerpointmodelsservice.h \
    dartscreatejsonfromdartspoint.h \
    dartscreatejsonmetadata.h \
    dartscreatepointindexes.h \
    dartscreatepointmodel.h \
    dartsdatacontextitemutility.h \
    dartsdatamodelpoint.h \
    dartsdbcreatejsonfrompoints.h \
    dartsdbcreatejsonfrompoints.h \
    dartsinput.h \
    dartsinputjsondb.h \
    dartsinputservices.h \
    dartsinputsjsondb.h \
    dartsmetadataservice.h \
    dartsmodelsservice.h \
    dartsmodelsservicescollection.h \
    dartsplayermodelbuilderservice.h \
    dartspmccolumnindexbuilder.h \
    dartspmcdatacontext.h \
    dartspmcsectionutility.h \
    dartspointindexes.h \
    dartspointsethint.h \
    dartspointsjsonservice.h \
    dartspointstringsuggestion.h \
    dartspscIndexBuilder.h \
    dartsroundindexbyattempt.h \
    dartssingleattemptinputrowsuggestion.h \
    dartstablecellcontext.h \
    dartstablecreatecolumnindices.h \
    dartstablecreatecolumns.h \
    dartstablecreaterowindices.h \
    dartstabledimensions.h \
    dartstablefillservice.h \
    dartstablemodel.h \
    dartstablesectionmanipulator.h \
    dartstableservices.h \
    dartstournamentjsonbuilder.h \
    dartstournamentnumberofattempts.h \
    dartstournamentservices.h \
    dartstournamentsjsondb.h \
    dartsutilityservices.h \
    dcbasicservices.h \
    dcbuilder.h \
    dcbuilderservices.h \
    dccreatecandidatetuples.h \
    dccreatescoretuples.h \
    dcindexcontroller.h \
    dcindexes.h \
    dcindexesbuilder.h \
    dcinitializeindexservice.h \
    dcinputmodel.h \
    dcjsonservices.h \
    dcmetainfo.h \
    dcmodel.h \
    dcplayer.h \
    dcplayerbuilder.h \
    dcreplacetuples.h \
    dcscoresservice.h \
    dctuple.h \
    dcturnvalues.h \
    dcturnvaluestojson.h \
    dcwinnerservice.h \
    defaultdartscellcontext.h \
    determinecontrollerstatebywinnerid.h \
    dpccreateinputmodels.h \
    dpcjsonservices.h \
    dpcontroller.h \
    dpcpointtojson.h \
    dpcservicesprovider.h \
    dpmctablemodel.h \
    dpscoresservices.h \
    dpsctablemodel.h \
    dsccalccandidate.h \
    dsccreateinputmodels.h \
    dscontroller.h \
    dscscoreservices.h \
    dscvaluesbuilder.h \
    dssctablemodel.h \
    extractwinnerinfofromjson.h \
    getdartspointfromdb.h \
    getdartstournamentfromdb.h \
    getdatafromdartstournament.h \
    getinputmodelsservice.h \
    getplayersfromdb.h \
    gettournamentwinner.h \
    greatestheight.h \
    greatestwidth.h \
    iadddetailstotournamentjson.h \
    iaddplayerdetailstomodel.h \
    iaddplayerdetailstotournament.h \
    iaddplayernamestojson.h \
    iaddtomodel.h \
    iaddtotalscoretodartsinputsjson.h \
    ibinaryservice.h \
    icomparison.h \
    iconnectcontroller.h \
    iconnectdartsmodelscontext.h \
    iconnectplayermodelscontext.h \
    iconnectroutebydisplayhint.h \
    iconnectroutebygamemode.h \
    iconnectroutebyinputhint.h \
    iconnectroutetoapplication.h \
    iconnectroutetodartsbuilder.h \
    iconnectservicesprovider.h \
    icountinputmodels.h \
    icreatedartstournamentsfromjson.h \
    icreatedcmetainfo.h \
    icreatedcturnvalues.h \
    icreatefromjson.h \
    icreatejsonfrom.h \
    icreatejsonfromdartspointindexes.h \
    icreatejsonfromdartstournaments.h \
    icreatejsonfromdcplayer.h \
    icreatejsonfromdcpoint.h \
    icreatejsonfrommodels.h \
    icreatejsonfromplayermodels.h \
    icreatejsonfromplayers.h \
    icreatejsonfromtournamentdetails.h \
    icreatemodel.h \
    icreatemodelfromstring.h \
    icreatemodelsfromjson.h \
    icreateplayerfromjson.h \
    icreateplayermodels.h \
    icreateplayersfromjson.h \
    icreatetournamentwinnerjson.h \
    idartsaddscore.h \
    idartscontrollerjsonservice.h \
    idartscontrollermodelsservice.h \
    idartscreateindexes.h \
    idartscreateinput.h \
    idartscreatejsonfrommodel.h \
    idartscreatejsonmetadata.h \
    idartsinputstojson.h \
    idartsinputsuggestion.h \
    idartsmetadata.h \
    idartsmodelscreatejsonfrompoints.h \
    idartsplayermodelbuilderservice.h \
    idartspointindexes.h \
    idartspointsethint.h \
    idartssubtractscores.h \
    idartstabledatacontext.h \
    idartstablesectionutility.h \
    idartstournamentjsonbuilder.h \
    idartstournamentnumberofattempts.h \
    idartstournamentsdb.h \
    idatamodelpoint.h \
    idatamodeltablecellsizes.h \
    idbcontext.h \
    idbgetindexesutility.h \
    idccalculatescore.h \
    idccreatescoretuples.h \
    idcgetplayerscore.h \
    idcindexes.h \
    idcindexesbuilder.h \
    idcindexestojson.h \
    idcindexservice.h \
    idcinitializeindexes.h \
    idcinputmodel.h \
    idcmetainfo.h \
    idcmodel.h \
    idcmodelcreator.h \
    idcmodeltojson.h \
    idcplayer.h \
    idcplayermodelbuilder.h \
    idcreplacetuples.h \
    idcscoresservice.h \
    idcturnvaluestojson.h \
    idcwinnerservice.h \
    idpcindexservice.h \
    idsccalccandidate.h \
    iextractwinnerinfo.h \
    ifilereader.h \
    ifilewriter.h \
    igenericjsonbuilder.h \
    igetdartspointfromdb.h \
    igetdartstournamentfromdb.h \
    igetdatafromdartstournament.h \
    igetdatafromdatacontext.h \
    igetinputmodelsservice.h \
    igetmodelsfromdb.h \
    igetplayerfromdb.h \
    igetpointinputfromdb.h \
    igetscoreinputfromdb.h \
    igettournamentfromdb.h \
    igettournamentwinner.h \
    iheaderlabels.h \
    ijson.h \
    ijsonbuilder.h \
    ijsonextractor.h \
    ijsontodcinputmodel.h \
    imergejson.h \
    imodelsdbcontext.h \
    inputmodelscountservice.h \
    inputmodelssortservice.h \
    iplayermodelscontext.h \
    ipredicate.h \
    iqmldatabuilder.h \
    iremovedartsinputsfromdb.h \
    iremovefromdb.h \
    iremovemodelsfromdb.h \
    irouteservicesprovider.h \
    iscoresservice.h \
    isetmodelhint.h \
    isortinputmodels.h \
    itablecellcontext.h \
    itablecolumnindexbuilder.h \
    itablefillcells.h \
    itableindicevalues.h \
    itablesectioncontext.h \
    itablesectionmanipulator.h \
    iternaryservice.h \
    itournamentjsonbuilder.h \
    iunaryservice.h \
    jsonarrayfromplayernamesandids.h \
    jsonmerger.h \
    jsonmodelsservice.h \
    abstractdartscontroller.h \
    AbstractApplicationInterface.h \
    IScoreBuilder.h \
    ScoreValidator.h \
    abstractcricketcontroller.h \
    abstractgamecontroller.h \
    abstractpersistence.h \
    dartapplication.h \
    dartstournamentmodel.h \
    idartsinput.h \
    idatacontext.h \
    imodel.h \
    iplayerinput.h \
    iplayermodel.h \
    ipointvalidator.h \
    iresponseinterface.h \
    iscoreparameter.h \
    itournament.h \
    itournamentbuilder.h \
    itournamentparameter.h \
    iurlparser.h \
    jsonplayersdbcontext.h \
    linkedlist.h \
    localdartapplication.h \
    localplayerscontext.h \
    localplayersdbcontext.h \
    mhtablecolumnwidth.h \
    mhtablerowheight.h \
    mhtablesectionmetrics.h \
    modelsdbioservices.h \
    modelsdbjsonservices.h \
    networkmanager.h \
    playermodel.h \
    playermodelscontext.h \
    playermodelsservices.h \
    pointvalidator.h \
    readbytearray.h \
    registerqmldartstabletypes.h \
    registerqmlsingletons.h \
    registerqmltableutils.h \
    removeinputsfromdb.h \
    removemodelsfromdb.h \
    replytimeout.h \
    routebydisplayhint.h \
    routebytournamentgamemode.h \
    routedartsbyinputhint.h \
    routeservicesprovider.h \
    setdartsmodelhint.h \
    sortdartspointinputsbyindexes.h \
    sortdartsscoreinputsbyindexes.h \
    testconfiguration.h \
    tournament.h \
    tournamentsjsondb.h \
    urlparser.h \
    testeventloop.h \
    verticalstringlabels.h \
    writebytearray.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
