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
    addtotalscoretodartsinputsjson.cpp \
    connectdartspointcontroller.cpp \
    connectdartsscorecontroller.cpp \
    connectdefaultmodelscontextinterface.cpp \
    createdartspointindexes.cpp \
    createdartspointsfromjson.cpp \
    createdartsscoreindexes.cpp \
    createjsonfromplayermodels.cpp \
    createplayersfromjson.cpp \
    dartapplication.cpp \
    dartscontrollerentity.cpp \
    dartscontrollerpointmodelsservice.cpp \
    dartscreatejsonfromscoreindexes.cpp \
    dartscreatejsonfromscores.cpp \
    dartsdatamodelpointbuilder.cpp \
    dartsdbcreatejsonfrompoints.cpp \
    dartsinputjsondb.cpp \
    dartsinputsfilterservice.cpp \
    dartsmultiscoredatamodel.cpp \
    dartsplayermodeldbmanipulator.cpp \
    dartsplayerpointservice.cpp \
    dartsplayerscoreservice.cpp \
    dartspointcontroller.cpp \
    dartspointcontrollerbuilder.cpp \
    dartspointinputstojson.cpp \
    dartspointmodelsservice.cpp \
    dartspointmulticolumndatamodel.cpp \
    dartspointsinglecolumndatamodel.cpp \
    dartspointsjsonservice.cpp \
    dartspointstringsuggestion.cpp \
    dartsscorebuilderservice.cpp \
    dartsscorecontroller.cpp \
    dartsscoreindexesbuilderservice.cpp \
    dartsscorejsonbuilderservice.cpp \
    dartsscoremodelmanipulator.cpp \
    dartsscoresinglecolumndatamodel.cpp \
    dartssingleattemptinputrowsuggestion.cpp \
    dartstournamentdbmanipulator.cpp \
    defaultdbmanipulatorservice.cpp \
    getdartsplayerdatafromdb.cpp \
    getdartsscorefromdb.cpp \
    getdartstournamentdatafromjson.cpp \
    getinputmodelsservice.cpp \
    getordereddartspointsbyjson.cpp \
    iurlparser.cpp \
    jsonpersistence.cpp \
    localdartsmodelsservice.cpp \
    main.cpp \
    networkmanager.cpp \
    playermodelsjsondb.cpp \
    remotemodelscontext.cpp \
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
    DefaultDartsServiceProvider.h \
    DefaultQtJsonBuilder.h \
    IConnect.h \
    IPointCalculatorService.h \
    abstractdartscontrollerbuilder.h \
    abstractdartsfilterpredicate.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractmodelsservice.h \
    abstractroutebygamemode.h \
    abstractroutebyinputhint.h \
    abstractroutedartsbydisplayhint.h \
    adddetailstotournamentjson.h \
    addplayernamestodartspointsjson.h \
    addplayernametodartsinputmodel.h \
    addtotalscoretodartsinputsjson.h \
    addtotalscoretodartspoint.h \
    addtotalscoretodartsscoremodel.h \
    createdartspointindexes.h \
    createdartsscoreindexes.h \
    assembledartsscoremodelfromjson.h\
    createjsonfromdartspointindexes.h \
    buildDartsPointTurnValues.h \
    builddartsscoreturnvalues.h \
    comparedartspointmodels.h \
    connectdartspointbuilder.h \
    connectdartspointcontroller.h \
    connectdartsscorecontroller.h \
    connectdefaultmodelscontextinterface.h \
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
    createplayersfromjson.h \
    dartscontrollerentity.h \
    dartscontrollerindexes.h \
    dartscontrollerplayer.h \
    dartscontrollerpoint.h \
    dartscontrollerpointmodelsservice.h \
    dartscontrollerscore.h \
    dartscreatejsonfromscoreindexes.h \
    dartscreatejsonfromscores.h \
    dartsdatamodelpoint.h \
    dartsdatamodelpointbuilder.h \
    dartsdbcreatejsonfrompoints.h \
    dartsdbcreatejsonfrompoints.h \
    dartsinputjsondb.h \
    dartsinputsfilterservice.h \
    dartsmetadataservice.h \
    dartsmodelmanipulator.h \
    dartsmodelsservicescollection.h \
    dartsmultiscoredatamodel.h \
    dartsplayer.h \
    dartsplayerbuilderservice.h \
    dartsplayerjsonbuilder.h \
    dartsplayermodelbuilder.h \
    dartsplayermodelbuilderservice.h \
    dartsplayermodeldbmanipulator.h \
    dartsplayerpointservice.h \
    dartsplayerscoreservice.h \
    dartspointbuilderservice.h \
    dartspointcontroller.h \
    dartspointcontrollerbuilder.h \
    dartspointdatamodelinjector.h \
    dartspointindexes.h \
    dartspointinputstojson.h \
    dartspointjsondb.h \
    dartspointmodelsservice.h \
    dartspointmulticolumndatamodel.h \
    dartspointsinglecolumndatamodel.h \
    dartspointsjsonservice.h \
    dartspointstringsuggestion.h \
    dartspointturnvalues.h \
    dartsscorebuilderservice.h \
    dartsscorecontroller.h \
    dartsscoreindexes.h \
    dartsscoreindexesbuilderservice.h \
    dartsscorejsoncreaterservice.h \
    dartsscorejsonbuilderservice.h \
    dartsscorejsondb.h \
    dartsscorelessthanpredicate.h \
    dartsscoremodelmanipulator.h \
    dartsscoremodelsbuilderservice.h \
    dartsscoresinglecolumndatamodel.h \
    dartsscoresjsoncreaterservice.h \
    dartsscoreturnvalues.h \
    dartssingleattemptinputrowsuggestion.h \
    dartstournamentbuilder.h \
    dartstournamentdbmanipulator.h \
    dartstournamentjsonbuilder.h \
    dartstournamentnumberofattempts.h \
    dartstournamentsjsondb.h \
    defaultdartspointcontroller.h \
    defaultdartsscorecontroller.h \
    defaultdbmanipulatorservice.h \
    defaultqtjsonextractor.h \
    determinecontrollerstatebywinnerid.h \
    getdartsplayerdatafromdb.h \
    getdartspointfromdb.h \
    getdartsscorefromdb.h \
    getdartstournamentdatafromjson.h \
    getdartstournamentfromdb.h \
    getdatafromdartstournament.h \
    getdatafromplayermodels.h \
    getinputmodelsservice.h \
    getordereddartspointsbyjson.h \
    iadddetailstotournamentjson.h \
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
    iconnectdartspointcontroller.h \
    iconnectdartsscorecontroller.h \
    iconnectmodelsinterface.h \
    iconnectroutebydisplayhint.h \
    iconnectroutebyinputhint.h \
    iconnectroutetoapplication.h \
    iconnectroutetodartsbuilder.h \
    iconvertpointtojson.h \
    icountinputmodels.h \
    icreatedartsindexes.h \
    icreatedartstournamentsfromjson.h \
    icreatefromjson.h \
    icreateinputmodelsfromjson.h \
    icreatejsonfrom.h \
    icreatejsonfromdartspointindexes.h \
    icreatejsonfromdartstournaments.h \
    icreatejsonfrominputs.h \
    icreatejsonfromplayermodels.h \
    icreateplayersfromjson.h \
    idartscontrollerentity.h \
    idartscontrollerindexesbuilder.h \
    idartscontrollerjsonservice.h \
    idartscontrollermodelsservice.h \
    idartscontrollerplayer.h \
    idartscontrollerpoint.h \
    idartscontrollerpointbuilder.h \
    idartscontrollerscore.h \
    idartscreatejsonfromscoreindexes.h \
    idartscreatejsonfromscores.h \
    idartsdatamodelpointbuilder.h \
    idartsinputdb.h \
    idartsinputsfilter.h \
    idartsinputstojson.h \
    idartsinputsuggestion.h \
    idartsmetadata.h \
    idartsmodelmanipulator.h \
    idartsmodelsbuilderservice.h \
    idartsmodelscreatejsonfrompoints.h \
    idartsplayer.h \
    idartsplayerbuilderservice.h \
    idartsplayerdbmanipulator.h \
    idartsplayerjsonbuilder.h \
    idartsplayermodelbuilder.h \
    idartsplayermodelbuilderservice.h \
    idartspointcontrollerindexes.h \
    idartspointindexes.h \
    idartspointindexservice.h \
    idartspointmodelmanipulator.h \
    idartsscorecontrollerindexes.h \
    idartsscoreindexes.h \
    idartsscoreindexservice.h \
    idartsscorejsonbuilderservice.h \
    idartsscoremodelmanipulator.h \
    idartstournamentdb.h \
    idartstournamentbuilder.h\
    idartstournamentjsonbuilder.h \
    idartstournamentnumberofattempts.h \
    idartstournamentsdbmanipulator.h \
    idatamodelpoint.h \
    igetdartsplayerdatafromdb.h \
    igetdartspointfromdb.h \
    igetdartsscorefromdb.h \
    igetdartstournamentdatafromjson.h \
    igetdartstournamentfromdb.h \
    igetdatafromdartstournament.h \
    igetdatafromjson.h \
    igetdatafromplayermodels.h \
    igetinputmodelsservice.h \
    igetordereddartspointsbyjson.h \
    igetplayerdatafromdb.h \
    igetpointinputfromdb.h \
    igetscoreinputfromdb.h \
    igettournamentfromdb.h \
    ijson.h \
    ijsonbuilder.h \
    ijsonextractor.h \
    imergejson.h \
    imodelsdbcontext.h \
    inputmodelscountservice.h \
    inputmodelssortservice.h \
    ipersistence.h \
    iplayerdbmanipulator.h \
    iplayerinputsdbmanipulatorservice.h \
    iplayerjsonbuilder.h \
    iplayermodelbuilder.h \
    iplayermodellistservice.h \
    iplayermodelsdb.h \
    iplayermodelsservice.h \
    iplayerpointservice.h \
    iplayerscoreservice.h \
    ipredicate.h \
    iqtjsonbuilder.h \
    iqtjsonextractor.h \
    isortinputmodels.h \
    iternaryservice.h \
    itournamentdbservice.h \
    itournamentjsonbuilder.h \
    itournamentmodelmanipulator.h \
    iunaryservice.h \
    jsonarrayfromplayernamesandids.h \
    jsondartsmodelsservice.h \
    jsonmergebybytearrayservice.h \
    jsonpersistence.h \
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
    idartsinputcreater.h \
    idartspointinput.h \
    idartsscoreinput.h \
    idartstournament.h \
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
    localdartsmodelsservice.h \
    networkmanager.h \
    playermodel.h \
    playermodelsjsondb.h \
    playermodelslocaljsondb.h \
    pointvalidator.h \
    remotemodelscontext.h \
    replytimeout.h \
    routebydisplayhint.h \
    routebytournamentgamemode.h \
    routedartsbyinputhint.h \
    scoreindexcontroller.h \
    setdartsmodelhint.h \
    sortdartspointinputsbyindexes.h \
    sortdartsscoreinputsbyindexes.h \
    testconfiguration.h \
    tournamentsjsondb.h \
    urlparser.h \
    testeventloop.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
