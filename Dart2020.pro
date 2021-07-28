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
    connectdartsmodelscontext.cpp \
    connectdartspointcontroller.cpp \
    connectdartsscorecontroller.cpp \
    createdartspointsfromjson.cpp \
    createdartsscoreindexes.cpp \
    createjsonfromplayermodels.cpp \
    createplayersfromjson.cpp \
    dartapplication.cpp \
    dartapplicationservices.cpp \
    dartscontrollerentity.cpp \
    dartscontrollerpointmodelsservice.cpp \
    dartscreatejsonfromscoreindexes.cpp \
    dartscreatejsonfromscores.cpp \
    dartscreatepointindexes.cpp \
    dartsdatamodelpointbuilder.cpp \
    dartsdbcreatejsonfrompoints.cpp \
    dartsinputjsondb.cpp \
    dartsinputservices.cpp \
    dartsmodelsservice.cpp \
    dartsmultiscoredatamodel.cpp \
    dartsplayerpointservice.cpp \
    dartsplayerscoreservice.cpp \
    dartspointcontroller.cpp \
    dartspointcontrollerbuilder.cpp \
    dartspointinputstojson.cpp \
    dartspointmulticolumndatamodel.cpp \
    dartspointsethint.cpp \
    dartspointsinglecolumndatamodel.cpp \
    dartspointsjsonservice.cpp \
    dartspointstringsuggestion.cpp \
    dartsscorebuilderservice.cpp \
    dartsscorecontroller.cpp \
    dartsscoreindexesbuilderservice.cpp \
    dartsscorejsonbuilderservice.cpp \
    dartsscoresethint.cpp \
    dartsscoresinglecolumndatamodel.cpp \
    dartssingleattemptinputrowsuggestion.cpp \
    dartstournamentservices.cpp \
    dartsutilityservices.cpp \
    extractwinnerinfofromjson.cpp \
    getdartsscorefromdb.cpp \
    getinputmodelsservice.cpp \
    getordereddartspointsbyjson.cpp \
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
    scoreindexcontroller.cpp \
    tournamentsjsondb.cpp \
    tst_Dart2020.cpp \
    urlparser.cpp \

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
    BuildDartsControllerEntity.h \
    CalculateScoreByDartsPointInput.h \
    ConnectDartsScoreBuilder.h \
    DartsIndexesBuilderService.h \
    DartsScoreMultiAttempIndexes.h \
    DefaultQtJsonBuilder.h \
    IConnect.h \
    IPointCalculatorService.h \
    abstractdartscontrollerbuilder.h \
    abstractdartsmodelscontext.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractdartstournament.h \
    abstractroutebydisplayhint.h \
    abstractroutebygamemode.h \
    abstractroutebyinputhint.h \
    adddetailstotournamentjson.h \
    addplayerdetailstotournament.h \
    addplayernamestodartspointsjson.h \
    addtotalscoretodartspoint.h \
    addtotalscoretodartspointsjson.h \
    addtotalscoretodartsscoremodel.h \
    connectdartsmodelscontext.h \
    connectplayerscontext.h \
    connectservices.h \
    connectservicesprovider.h \
    createdartsscoreindexes.h \
    createdartstournamentfromjson.h \
    createjsonfromdartspointindexes.h \
    buildDartsPointTurnValues.h \
    builddartsscoreturnvalues.h \
    comparedartspointmodels.h \
    connectdartspointbuilder.h \
    connectdartspointcontroller.h \
    connectdartsscorecontroller.h \
    connectroutebydisplayhint.h \
    connectroutebygamemode.h \
    connectroutebyinputhint.h \
    convertpointtojson.h \
    createdartspointsfromjson.h \
    createdartsscoremodelsfromjson.h \
    createdartstournamentsfromjson.h \
    createjsonfromdartsscoremodels.h \
    createjsonfromdartstournaments.h \
    createjsonfromplayermodels.h \
    createjsonfromplayers.h \
    createjsonfromtournamentdetails.h \
    createplayerfromjson.h \
    createplayermodels.h \
    createplayersfromjson.h \
    dartapplicationservices.h \
    dartscontrollerentity.h \
    dartscontrollerindexes.h \
    dartscontrollerplayer.h \
    dartscontrollerpoint.h \
    dartscontrollerpointmodelsservice.h \
    dartscontrollerscore.h \
    dartscreatejsonfromdartspoint.h \
    dartscreatejsonfromdartsscore.h \
    dartscreatejsonfromscoreindexes.h \
    dartscreatejsonfromscores.h \
    dartscreatejsonmetadata.h \
    dartscreatepointindexes.h \
    dartscreatepointmodel.h \
    dartscreatescoremodel.h \
    dartsdatamodelpoint.h \
    dartsdatamodelpointbuilder.h \
    dartsdbcreatejsonfrompoints.h \
    dartsdbcreatejsonfrompoints.h \
    dartsinputjsondb.h \
    dartsinputservices.h \
    dartsmetadataservice.h \
    dartsmodelsservice.h \
    dartsmodelsservicescollection.h \
    dartsmultiscoredatamodel.h \
    dartsplayer.h \
    dartsplayerbuilderservice.h \
    dartsplayermodelbuilderservice.h \
    dartsplayerpointservice.h \
    dartsplayerscoreservice.h \
    dartspointbuilderservice.h \
    dartspointcontroller.h \
    dartspointcontrollerbuilder.h \
    dartspointdatamodelinjector.h \
    dartspointindexes.h \
    dartspointinputstojson.h \
    dartspointjsondb.h \
    dartspointmulticolumndatamodel.h \
    dartspointsethint.h \
    dartspointsinglecolumndatamodel.h \
    dartspointsjsonservice.h \
    dartspointstringsuggestion.h \
    dartspointturnvalues.h \
    dartsscorebuilderservice.h \
    dartsscorecontroller.h \
    dartsscoreindexes.h \
    dartsscoreindexesbuilderservice.h \
    dartsscorejsonbuilderservice.h \
    dartsscorejsondb.h \
    dartsscorelessthanpredicate.h \
    dartsscoremodelsbuilderservice.h \
    dartsscoresethint.h \
    dartsscoresinglecolumndatamodel.h \
    dartsscoreturnvalues.h \
    dartssingleattemptinputrowsuggestion.h \
    dartstournamentjsonbuilder.h \
    dartstournamentnumberofattempts.h \
    dartstournamentservices.h \
    dartstournamentsjsondb.h \
    dartsutilityservices.h \
    defaultdartspointcontroller.h \
    defaultdartsscorecontroller.h \
    defaultqtjsonextractor.h \
    determinecontrollerstatebywinnerid.h \
    extractwinnerinfofromjson.h \
    getdartspointfromdb.h \
    getdartsscorefromdb.h \
    getdartstournamentfromdb.h \
    getdatafromdartstournament.h \
    getinputmodelsservice.h \
    getordereddartspointsbyjson.h \
    getplayersfromdb.h \
    gettournamentwinner.h \
    iadddetailstotournamentjson.h \
    iaddplayerdetailstomodel.h \
    iaddplayerdetailstotournament.h \
    iaddplayernamestojsonentity.h \
    iaddscoretodartsscoremodel.h \
    iaddtomodel.h \
    iaddtotalscoretodartsinputsjson.h \
    iaddtotalscoretodartspoint.h \
    ibinaryservice.h \
    ibuildcontrollerturnvalues.h \
    ibuilddartspointturnvalues.h \
    ibuilddartsscorecontrollervalues.h \
    ibytearrayjsonmerger.h \
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
    iconvertpointtojson.h \
    icountinputmodels.h \
    icreatedartstournamentsfromjson.h \
    icreatefromjson.h \
    icreatejsonfrom.h \
    icreatejsonfromdartspointindexes.h \
    icreatejsonfromdartstournaments.h \
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
    idartscontrollerentity.h \
    idartscontrollerindexesbuilder.h \
    idartscontrollerjsonservice.h \
    idartscontrollermodelsservice.h \
    idartscontrollerplayer.h \
    idartscontrollerpoint.h \
    idartscontrollerpointbuilder.h \
    idartscontrollerscore.h \
    idartscreateindexes.h \
    idartscreateinput.h \
    idartscreatejsonfrommodel.h \
    idartscreatejsonfromscoreindexes.h \
    idartscreatejsonfromscores.h \
    idartscreatejsonmetadata.h \
    idartsdatamodelpointbuilder.h \
    idartsinputstojson.h \
    idartsinputsuggestion.h \
    idartsmetadata.h \
    idartsmodelsbuilderservice.h \
    idartsmodelscreatejsonfrompoints.h \
    idartsplayer.h \
    idartsplayerbuilderservice.h \
    idartsplayermodelbuilderservice.h \
    idartspointcontrollerindexes.h \
    idartspointindexes.h \
    idartspointindexservice.h \
    idartspointsethint.h \
    idartsscorecontrollerindexes.h \
    idartsscoreindexes.h \
    idartsscoreindexservice.h \
    idartsscorejsonbuilderservice.h \
    idartsscoresethint.h \
    idartstournamentjsonbuilder.h \
    idartstournamentnumberofattempts.h \
    idartstournamentsdb.h \
    idatamodelpoint.h \
    idbcontext.h \
    idbgetindexesutility.h \
    iextractwinnerinfo.h \
    ifilereader.h \
    ifilewriter.h \
    igetdartspointfromdb.h \
    igetdartsscorefromdb.h \
    igetdartstournamentfromdb.h \
    igetdatafromdartstournament.h \
    igetinputmodelsservice.h \
    igetmodelsfromdb.h \
    igetordereddartspointsbyjson.h \
    igetplayerfromdb.h \
    igetpointinputfromdb.h \
    igetscoreinputfromdb.h \
    igettournamentfromdb.h \
    igettournamentwinner.h \
    ijson.h \
    ijsonbuilder.h \
    ijsonextractor.h \
    imergejson.h \
    imodelsdbcontext.h \
    inputmodelscountservice.h \
    inputmodelssortservice.h \
    iplayermodelscontext.h \
    iplayerpointservice.h \
    iplayerscoreservice.h \
    ipredicate.h \
    iqtjsonbuilder.h \
    iqtjsonextractor.h \
    iremovedartsinputsfromdb.h \
    iremovefromdb.h \
    iremovemodelsfromdb.h \
    irouteservicesprovider.h \
    isortinputmodels.h \
    iternaryservice.h \
    itournamentjsonbuilder.h \
    iunaryservice.h \
    jsonarrayfromplayernamesandids.h \
    jsonmergebybytearrayservice.h \
    jsonmodelsservice.h \
    abstractdartscontroller.h \
    AbstractApplicationInterface.h \
    IControllerBuilder.h \
    IScoreBuilder.h \
    LinkedList.h \
    PointIndexController.h \
    ScoreValidator.h \
    abstractcricketcontroller.h \
    abstractgamecontroller.h \
    abstractpersistence.h \
    dartapplication.h \
    dartspointinput.h \
    dartsscoreinput.h \
    dartstournamentmodel.h \
    idartsinput.h \
    idartspointinput.h \
    idartsscoreinput.h \
    idatacontext.h \
    imodel.h \
    iplayerinput.h \
    iplayermodel.h \
    ipointvalidator.h \
    iresponseinterface.h \
    iscoreparameter.h \
    iscorevalidator.h \
    itournament.h \
    itournamentbuilder.h \
    itournamentparameter.h \
    iurlparser.h \
    jsonplayersdbcontext.h \
    localdartapplication.h \
    localplayerscontext.h \
    localplayersdbcontext.h \
    modelsdbioservices.h \
    modelsdbjsonservices.h \
    networkmanager.h \
    playermodel.h \
    playermodelscontext.h \
    playermodelsservices.h \
    pointcontrollerserviceprovider.h \
    pointvalidator.h \
    readbytearray.h \
    removeinputsfromdb.h \
    removemodelsfromdb.h \
    replytimeout.h \
    routebydisplayhint.h \
    routebytournamentgamemode.h \
    routedartsbyinputhint.h \
    routeservicesprovider.h \
    scoreindexcontroller.h \
    setdartsmodelhint.h \
    sortdartspointinputsbyindexes.h \
    sortdartsscoreinputsbyindexes.h \
    testconfiguration.h \
    tournament.h \
    tournamentsjsondb.h \
    urlparser.h \
    testeventloop.h \
    writebytearray.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
