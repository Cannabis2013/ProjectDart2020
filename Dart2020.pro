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
    assembledartstournamentmodelfromjson.cpp\
    abstractjsonpersistence.cpp \
    assemblejsonarrayfromdartspoints.cpp \
    assemblesingleattemptpointsfromjson.cpp \
    builddartspointservicewithlocaljsondb.cpp \
    builddartsscoreservicewithlocaljsondb.cpp \
    connectcontrollerbuilder.cpp \
    connectdartsmultiattemptcontroller.cpp \
    connectdartssingleattemptpointcontroller.cpp \
    connectdefaultmodelscontextinterface.cpp \
    dartapplication.cpp \
    dartscontrollerbuilder.cpp \
    dartscontrollerentity.cpp \
    dartscontrollerpointmodelsservice.cpp \
    dartsinputsfilterservice.cpp \
    dartsjsonservice.cpp \
    dartsjsonservicebuilder.cpp \
    dartsmodelsservice.cpp \
    dartsmodelsservicebuilder.cpp \
    dartsmultiscoredatamodel.cpp \
    dartsplayerpointservice.cpp \
    dartsplayerscoreservice.cpp \
    dartspointjsondbservice.cpp \
    dartspointjsonservice.cpp \
    dartspointlogisticcontroller.cpp \
    dartspointmodelsservice.cpp \
    dartspointsingleattempt.cpp \
    dartspointsingleattemptdatamodel.cpp \
    dartspointsjsonservice.cpp \
    dartsscoreindexesbuilderservice.cpp \
    dartsscorejsonbuilderservice.cpp \
    dartsscorejsondb.cpp \
    dartsscorejsonservice.cpp \
    dartsscorelogisticcontroller.cpp \
    dartsscoremodelsservice.cpp \
    dartsscoremultiattempt.cpp \
    dartssingleattemptindexesbuilder.cpp \
    dartstournamentjsonextractor.cpp \
    defaultdbmanipulatorservice.cpp \
    defaultmodelsservicebuilder.cpp \
    filterpredicatedefaultbuilder.cpp \
    getinputmodelsservice.cpp \
    iurlparser.cpp \
    localmodelsservice.cpp \
    localplayermodelsservice.cpp \
    main.cpp \
    multiattemptscoredatamodel.cpp \
    networkmanager.cpp \
    playerjsonservicebuilder.cpp \
    playermodelsjsonassembler.cpp \
    playermodelsjsonextractor.cpp \
    playermodelsjsonservice.cpp \
    playermodelsservicebuilder.cpp \
    playersjsondb.cpp \
    remotemodelscontext.cpp \
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
    ApplicationBuilder.h \
    AssembleDartsTournamentsFromJsonArray.h \
    BuildDartsControllerEntity.h \
    DartsIndexesBuilderService.h \
    DartsPointCalculator.h \
    DartsScoreJsonExtractor.h \
    DartsScoreMultiAttempIndexes.h \
    IPointCalculatorService.h \
    abstractdartscontrollerbuilder.h \
    abstractdartsfilterpredicate.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractmodelsservice.h \
    abstractmodelsservicebuilder.h \
    addaccumulatedscoretodartsscore.h \
    addplayernametodartsinputmodel.h \
    addwinnernametotournamentjson.h \
    assembleJsonFromDartsIndexesAndPoints.h \
    assembledartspointmodelfromjson.h \
    assembledartsscorefromjson.h\
    assembledartsscoremodelfromjson.h \
    assembledartsscoreturnvalues.h \
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
    assemblesingleattemptpointsfromjson.h \
    assignplayeridstodartstournamentmodel.h \
    buildDartsPointTurnValues.h \
    builddartspointservicewithlocaljsondb.h \
    builddartsscoreservicewithlocaljsondb.h \
    comparedartspointmodels.h \
    connectcontrollerbuilder.h \
    connectdartsmultiattemptcontroller.h \
    connectdartssingleattemptpointcontroller.h \
    connectdefaultmodelscontextinterface.h \
    dartscontrollerbuilder.h \
    dartscontrollerentity.h \
    dartscontrollerplayer.h \
    dartscontrollerpoint.h \
    dartscontrollerpointbuilder.h \
    dartscontrollerpointmodelsservice.h \
    dartscontrollerscore.h \
    dartsinputmodelhintservice.h \
    dartsinputsfilterservice.h \
    dartsjsonservice.h \
    dartsjsonservicebuilder.h \
    dartsmodelsservice.h \
    dartsmodelsservicebuilder.h \
    dartsmodelsservicescollection.h \
    dartsmultiscoredatamodel.h \
    dartsplayer.h \
    dartsplayerbuilderservice.h \
    dartsplayermodelbuilderservice.h \
    dartsplayerpointservice.h \
    dartsplayerscoreservice.h \
    dartspointindexes.h \
    dartspointjsondbservice.h \
    dartspointjsonservice.h \
    dartspointlogisticcontroller.h \
    dartspointmodelsservice.h \
    dartspointsingleattempt.h \
    dartspointsingleattemptdatamodel.h \
    dartspointsjsonservice.h \
    dartspointturnvalues.h \
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
    dartsscoremultiattempt.h \
    dartsscoresjsonassemblerservice.h \
    dartsscoreturnvalues.h \
    dartssingleattemptindexes.h \
    dartssingleattemptindexesbuilder.h \
    dartstournamentbuilder.h \
    defaultdbmanipulatorservice.h \
    defaultmodelsservicebuilder.h \
    deletetournamentsbyindexesservice.h \
    determinecontrollerstatebywinnerid.h \
    filterpredicatedefaultbuilder.h \
    getdartsscoreindexesbymodel.h \
    getdartstournamentbyid.h \
    getdartstournamentbyindexservice.h \
    getdeleteplayerindexfromjson.h \
    getinputmodelsservice.h \
    getplayerindexesfromjson.h \
    gettournamentidbyjson.h \
    gettournamentindexesfromjson.h \
    getwinneridbyjson.h \
    ibinaryservice.h \
    icomparison.h \
    idartscontrollerentity.h \
    idartscontrollerindexesbuilder.h \
    idartscontrollermodelsservice.h \
    idartscontrollerplayer.h \
    idartscontrollerpoint.h \
    idartscontrollerpointbuilder.h \
    idartscontrollerscore.h \
    idartsinputsfilter.h \
    idartsjsonextractor.h \
    idartsjsonservice.h \
    idartsjsonservicebuilder.h \
    idartslogisticsservice.h \
    idartsmodelsbuilderservice.h \
    idartsmodelsservice.h \
    idartsmultiattemptindexes.h \
    idartsmultiattemptindexesbuilder.h \
    idartsmultiattemptindexservice.h \
    idartsplayer.h \
    idartsplayerbuilderservice.h \
    idartsplayermodelbuilderservice.h \
    idartspointdb.h \
    idartspointindexes.h \
    idartspointjsonservice.h \
    idartspointmodelsservice.h \
    idartspointsjsonservice.h \
    idartsscoredb.h \
    idartsscoreindexes.h \
    idartsscorejsonbuilderservice.h \
    idartsscorejsonservice.h \
    idartsscoremodelsservice.h \
    idartssingleattemptindexes.h \
    idartssingleattemptindexesbuilder.h \
    idartssingleattemptindexservice.h \
    idartstournamentdb.h \
    idartstournamentbuilder.h\
    ifilterpredicatebuilder.h \
    igetinputmodelsservice.h \
    iinputmodelscountservice.h \
    ijsonmodelsservice.h \
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
    iternaryservice.h \
    iunaryservice.h \
    jsonarrayfromplayernamesandids.h \
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
    multiattemptscoredatamodel.h \
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
