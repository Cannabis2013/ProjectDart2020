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
    connectcontrollerbuilder.cpp \
    connectdartsscorecontroller.cpp \
    connectdartssingleattemptpointcontroller.cpp \
    connectdartssinglescorecontroller.cpp \
    connectdefaultmodelscontextinterface.cpp \
    dartapplication.cpp \
    dartscontrollerbuilder.cpp \
    dartsjsonservicebuilder.cpp \
    dartsmodelsjsonservice.cpp \
    dartsmodelsservice.cpp \
    dartsmodelsservicebuilder.cpp \
    dartsmultipointdatamodel.cpp \
    dartsmultiscoredatamodel.cpp \
    dartsplayerscoreservice.cpp \
    dartspointdbservice.cpp \
    dartspointsingleattempt.cpp \
    dartsscoremultiattempt.cpp \
    dartssingleattemptpointjsonservice.cpp \
    dartstournamentjsonextractor.cpp \
    defaultmodelsservicebuilder.cpp \
    iurlparser.cpp \
    localmodelsservice.cpp \
    localplayermodelsservice.cpp \
    main.cpp \
    networkmanager.cpp \
    playermodelsjsonassembler.cpp \
    playermodelsjsonextractor.cpp \
    playermodelsservicebuilder.cpp \
    playersjsondb.cpp \
    pointlogisticcontroller.cpp \
    remotemodelscontext.cpp \
    scoreindexcontroller.cpp \
    scorelogisticcontroller.cpp \
    sftpdatamodel.cpp \
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
    IDartsSingleAttemptPointJsonService.h \
    abstractdartscontrollerbuilder.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractmodelsservice.h \
    abstractmodelsservicebuilder.h \
    addplayernametopointjson.h \
    assembleJsonFromDartsIndexesAndPoints.h \
    assembledartspointindexesbydartspointmodel.h \
    assembledartspointmodelfromjson.h \
    assembledartsscorefromjson.h\
    assemblejsonarrayfromdartspoints.h \
    assemblejsonbasictournamentvalues.h \
    assemblejsonbasictournamentvaluesfrommodel.h \
    assemblejsondartstournamentmodels.h \
    assemblejsonfromdartspointindexes.h \
    assemblejsonfromdartspointmodel.h \
    assemblejsonfromdartspoints.h \
    assemblejsonfromdartstournamentmodels.h \
    assemblejsonfromordereddartspointmodels.h \
    assemblejsonfromplayeridandname.h \
    assembleplayermodelfromjson.h \
    assemblesingleattemptpointsfromjson.h \
    assignplayeridstodartstournamentmodel.h \
    connectcontrollerbuilder.h \
    connectdartsscorecontroller.h \
    connectdartssingleattemptpointcontroller.h \
    connectdartssinglescorecontroller.h \
    connectdefaultmodelscontextinterface.h \
    dartscontrollerbuilder.h \
    dartsjsonservicebuilder.h \
    dartsmodelsjsonservice.h \
    dartsmodelsservice.h \
    dartsmodelsservicebuilder.h \
    dartsmodelsservicescollection.h \
    dartsmultipointdatamodel.h \
    dartsmultiscoredatamodel.h \
    dartsplayerscoreservice.h \
    dartspointdbservice.h \
    dartspointindexes.h \
    dartspointsingleattempt.h \
    dartsscorejsonassemblerservice.h \
    dartsscoremultiattempt.h \
    dartsscoresjsonassemblerservice.h \
    dartssingleattemptpointjsonservice.h \
    defaultmodelsservicebuilder.h \
    getdeleteplayerindexfromjson.h \
    getordereddartspointmodels.h \
    getplayerindexesfromjson.h \
    gettournamentindexesfromjson.h \
    ibinaryservice.h \
    idartsjsonservice.h \
    idartsmodelsservice.h \
    idartspointdb.h \
    idartspointindexes.h \
    idartstournamentdb.h \
    imodelsservicebuilder.h \
    ipersistence.h \
    iplayermodelsservice.h \
    iplayerscoreservice.h \
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
    ftplogisticcontrollerinterface.h \
    idartsinput.h \
    idartsinputassembler.h \
    idartsinputjsonextractor.h \
    idartspointinput.h \
    idartsscoreinput.h \
    idartstournament.h \
    idartstournamentjsonextractorservice.h \
    idartstournamentsjsonassemblerservice.h \
    idatacontext.h \
    imodel.h \
    imodelsdbcontext.h \
    indexcontrollerinterface.h \
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
    playermodel.h \
    playermodelsjsonassembler.h \
    playermodelsjsonextractor.h \
    playermodelsservicebuilder.h \
    playersjsondb.h \
    pointScoreCalculator.h \
    pointlogisticcontroller.h \
    pointvalidator.h \
    remotemodelscontext.h \
    replytimeout.h \
    scoreCalculatorInterface.h \
    scorecalculator.h \
    scoreindexcontroller.h \
    scorelogisticcontroller.h \
    sftpdatamodel.h \
    testconfiguration.h \
    tournamentjsondb.h \
    tournamentsjsonassemblerservice.h \
    urlparser.h \
    testeventloop.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
