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
    addtotalscoretodartsinputsjson.cpp \
    assembledartspointsfromjson.cpp \
    assembledartstournamentmodelfromjson.cpp\
    abstractjsonpersistence.cpp \
    assemblejsonarrayfromdartspoints.cpp \
    builddartspointservicewithlocaljsondb.cpp \
    builddartsscoreservicewithlocaljsondb.cpp \
    connectdartspointcontroller.cpp \
    connectdartsscorecontroller.cpp \
    connectdefaultmodelscontextinterface.cpp \
    dartapplication.cpp \
    dartscontrollerentity.cpp \
    dartscontrollerpointmodelsservice.cpp \
    dartsdatamodelpointbuilder.cpp \
    dartsinputsfilterservice.cpp \
    dartsjsonservice.cpp \
    dartsjsonservicebuilder.cpp \
    dartsmodelsservice.cpp \
    dartsmodelsservicebuilder.cpp \
    dartsmultiscoredatamodel.cpp \
    dartsplayerpointservice.cpp \
    dartsplayerscoreservice.cpp \
    dartspointcontroller.cpp \
    dartspointcontrollerbuilder.cpp \
    dartspointinputstojson.cpp \
    dartspointjsondbservice.cpp \
    dartspointlogisticcontroller.cpp \
    dartspointmodelsservice.cpp \
    dartspointmulticolumndatamodel.cpp \
    dartspointsinglecolumndatamodel.cpp \
    dartspointsjsonservice.cpp \
    dartsscorebuilderservice.cpp \
    dartsscorecontroller.cpp \
    dartsscoreindexesbuilderservice.cpp \
    dartsscorejsonbuilderservice.cpp \
    dartsscorejsondb.cpp \
    dartsscorejsonservice.cpp \
    dartsscorelogisticcontroller.cpp \
    dartsscoremodelsservice.cpp \
    dartsscoresinglecolumndatamodel.cpp \
    dartssingleattemptindexesbuilder.cpp \
    dartstournamentjsonextractor.cpp \
    defaultdbmanipulatorservice.cpp \
    defaultmodelsservicebuilder.cpp \
    filterpredicatedefaultbuilder.cpp \
    getinputmodelsservice.cpp \
    getordereddartspointsbyjson.cpp \
    iurlparser.cpp \
    localmodelsservice.cpp \
    localplayermodelsservice.cpp \
    main.cpp \
    networkmanager.cpp \
    playerjsonservicebuilder.cpp \
    playermodelsjsonassembler.cpp \
    playermodelsjsonextractor.cpp \
    playermodelsjsonservice.cpp \
    playermodelsservicebuilder.cpp \
    playersjsondb.cpp \
    remotemodelscontext.cpp \
    routebydisplayhint.cpp \
    routedartsbyinputhint.cpp \
    scoreindexcontroller.cpp \
    tournamentjsondb.cpp \
    tournamentsjsonassembler.cpp \
    tournamentsjsonassemblerservice.cpp \
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
    AssembleDartsTournamentsFromJsonArray.h \
    BuildDartsControllerEntity.h \
    CalculateScoreByDartsPointInput.h \
    ConnectDartsScoreBuilder.h \
    DartsIndexesBuilderService.h \
    DartsScoreMultiAttempIndexes.h \
    DefaultQtJsonBuilder.h \
    IConnect.h \
    IPointCalculatorService.h \
    abstractdartscontrollerbuilder.h \
    abstractdartsfilterpredicate.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractmodelsservice.h \
    abstractmodelsservicebuilder.h \
    abstractroutebygamemode.h \
    abstractroutebyinputhint.h \
    abstractroutedartsbydisplayhint.h \
    addplayernamestodartspointsjson.h \
    addplayernametodartsinputmodel.h \
    addtotalscoretodartsinputsjson.h \
    addtotalscoretodartspoint.h \
    addtotalscoretodartsscoremodel.h \
    addwinnernametotournamentjson.h \
    assembleJsonFromDartsIndexesAndPoints.h \
    assembledartspointmodelfromjson.h \
    assembledartspointsfromjson.h \
    assembledartsscorefromjson.h\
    assembledartsscoremodelfromjson.h \
    assemblejsonarrayfromdartspoints.h \
    assemblejsonbasictournamentvalues.h \
    assemblejsonbasictournamentvaluesfrommodel.h \
    assemblejsonbydartsscoreindexes.h \
    assemblejsonbydartsscoremodels.h \
    assemblejsondartstournamentmodels.h \
    assemblejsonfromdartsmultiattemptscores.h \
    assemblejsonfromdartspointindexes.h \
    assemblejsonfromdartspoints.h \
    assemblejsonfromdartstournamentmodels.h \
    assemblejsonfromordereddartspointmodels.h \
    assemblejsonfromplayeridandname.h \
    assemblemultiattemptscoresbyjson.h \
    assembleplayermodelfromjson.h \
    assignplayeridstodartstournamentmodel.h \
    buildDartsPointTurnValues.h \
    builddartspointservicewithlocaljsondb.h \
    builddartsscoreservicewithlocaljsondb.h \
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
    dartscontrollerentity.h \
    dartscontrollerindexes.h \
    dartscontrollerplayer.h \
    dartscontrollerpoint.h \
    dartscontrollerpointmodelsservice.h \
    dartscontrollerscore.h \
    dartsdatamodelpoint.h \
    dartsdatamodelpointbuilder.h \
    dartsinputmodelhintservice.h \
    dartsinputsfilterservice.h \
    dartsjsonservice.h \
    dartsjsonservicebuilder.h \
    dartsmetadataservice.h \
    dartsmodelsservice.h \
    dartsmodelsservicebuilder.h \
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
    dartspointjsondbservice.h \
    dartspointlogisticcontroller.h \
    dartspointmodelsservice.h \
    dartspointmulticolumndatamodel.h \
    dartspointsinglecolumndatamodel.h \
    dartspointsjsonservice.h \
    dartspointturnvalues.h \
    dartsscorebuilderservice.h \
    dartsscorecontroller.h \
    dartsscoreindexes.h \
    dartsscoreindexesbuilderservice.h \
    dartsscorejsonassemblerservice.h \
    dartsscorejsonbuilderservice.h \
    dartsscorejsondb.h \
    dartsscorejsonservice.h \
    dartsscorelessthanpredicate.h \
    dartsscorelogisticcontroller.h \
    dartsscoremodelsbuilderservice.h \
    dartsscoremodelsservice.h \
    dartsscoresinglecolumndatamodel.h \
    dartsscoresjsonassemblerservice.h \
    dartsscoreturnvalues.h \
    dartssingleattemptindexesbuilder.h \
    dartstournamentbuilder.h \
    defaultdartspointcontroller.h \
    defaultdartsscorecontroller.h \
    defaultdbmanipulatorservice.h \
    defaultmodelsservicebuilder.h \
    defaultqtjsonextractor.h \
    deletetournamentsbyindexesservice.h \
    determinecontrollerstatebywinnerid.h \
    filterpredicatedefaultbuilder.h \
    getdartsscoreindexesbymodel.h \
    getdartstournamentbyid.h \
    getdartstournamentbyindexservice.h \
    getdeleteplayerindexfromjson.h \
    getinputmodelsservice.h \
    getordereddartspointsbyjson.h \
    getplayerindexesfromjson.h \
    gettournamentidbyjson.h \
    gettournamentindexesfromjson.h \
    getwinneridbyjson.h \
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
    idartscontrollerentity.h \
    idartscontrollerindexesbuilder.h \
    idartscontrollerjsonservice.h \
    idartscontrollermodelsservice.h \
    idartscontrollerplayer.h \
    idartscontrollerpoint.h \
    idartscontrollerpointbuilder.h \
    idartscontrollerscore.h \
    idartsdatamodelpointbuilder.h \
    idartsinputsfilter.h \
    idartsinputstojson.h \
    idartsjsonservice.h \
    idartsjsonservicebuilder.h \
    idartslogisticsservice.h \
    idartsmetadata.h \
    idartsmodelsbuilderservice.h \
    idartsmodelsservice.h \
    idartsmultiattemptindexesbuilder.h \
    idartsplayer.h \
    idartsplayerbuilderservice.h \
    idartsplayermodelbuilderservice.h \
    idartspointcontrollerindexes.h \
    idartspointdb.h \
    idartspointindexes.h \
    idartspointindexservice.h \
    idartspointmodelsservice.h \
    idartspointsjsonservice.h \
    idartsscorecontrollerindexes.h \
    idartsscoredb.h \
    idartsscoreindexes.h \
    idartsscoreindexservice.h \
    idartsscorejsonbuilderservice.h \
    idartsscorejsonservice.h \
    idartsscoremodelsservice.h \
    idartssingleattemptindexesbuilder.h \
    idartstournamentdb.h \
    idartstournamentbuilder.h\
    idatamodelpoint.h \
    ifilterpredicatebuilder.h \
    igetinputmodelsservice.h \
    igetordereddartspointsbyjson.h \
    iinputmodelscountservice.h \
    ijson.h \
    ijsonbuilder.h \
    ijsonextractor.h \
    imergejson.h \
    imodelsdbcontext.h \
    imodelsservicebuilder.h \
    inputmodelscountservice.h \
    inputmodelssortservice.h \
    ipersistence.h \
    iplayerinputsdbmanipulatorservice.h \
    iplayermodelsdb.h \
    iplayermodelsjsonservice.h \
    iplayermodelsservice.h \
    iplayerpointservice.h \
    iplayerscoreservice.h \
    ipredicate.h \
    iqtjsonbuilder.h \
    iqtjsonextractor.h \
    iternaryservice.h \
    iunaryservice.h \
    jsonarrayfromplayernamesandids.h \
    jsonmergebybytearrayservice.h \
    localmodelsservice.h \
    assembledartstournamentmodelfromjson.h\
    abstractdartscontroller.h \
    AbstractApplicationInterface.h \
    IControllerBuilder.h \
    IScoreBuilder.h \
    LinkedList.h \
    PointIndexController.h \
    ScoreValidator.h \
    abstractcricketcontroller.h \
    abstractgamecontroller.h \
    abstractjsonpersistence.h \
    abstractpersistence.h \
    dartapplication.h \
    dartspointinput.h \
    dartsscoreinput.h \
    dartstournamentjsonextractor.h \
    dartstournamentmodel.h \
    idartsinput.h \
    idartsinputassembler.h \
    idartspointinput.h \
    idartsscoreinput.h \
    idartstournament.h \
    idartstournamentjsonextractorservice.h \
    idartstournamentsjsonassemblerservice.h \
    idatacontext.h \
    imodel.h \
    iplayerinput.h \
    iplayerjsonassemblerservice.h \
    iplayerjsonextractorservice.h \
    iplayermodel.h \
    ipointvalidator.h \
    iresponseinterface.h \
    iscoreparameter.h \
    iscorevalidator.h \
    itournament.h \
    itournamentbuilder.h \
    itournamentparameter.h \
    iurlparser.h \
    jsonextractor.h \
    localplayermodelsservice.h \
    networkmanager.h \
    playerjsonservicebuilder.h \
    playermodel.h \
    playermodelsjsonassembler.h \
    playermodelsjsonextractor.h \
    playermodelsjsonservice.h \
    playermodelsservicebuilder.h \
    playersjsondb.h \
    pointvalidator.h \
    remotemodelscontext.h \
    replytimeout.h \
    routebydisplayhint.h \
    routebytournamentgamemode.h \
    routedartsbyinputhint.h \
    scoreindexcontroller.h \
    setdartsmodelhint.h \
    sortdartspointinputsbyindexes.h \
    testconfiguration.h \
    tournamentjsondb.h \
    tournamentsjsonassemblerservice.h \
    urlparser.h \
    testeventloop.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
