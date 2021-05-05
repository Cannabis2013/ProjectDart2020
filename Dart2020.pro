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
    connectdartspointcontroller.cpp \
    connectdartsscorecontroller.cpp \
    dartapplication.cpp \
    dartscontrollerbuilder.cpp \
    dartsinputjsonassembler.cpp \
    dartsinputjsonextractor.cpp \
    dartsmodelsservice.cpp \
    dartsmultipointdatamodel.cpp \
    dartsmultiscoredatamodel.cpp \
    dartspointdbservice.cpp \
    dartsscorecontroller.cpp \
    dartstournamentjsonextractor.cpp \
    iurlparser.cpp \
    localcricketcontroller.cpp \
    localmodelsservice.cpp \
    localplayermodelscontext.cpp \
    main.cpp \
    networkmanager.cpp \
    playerjsonassembler.cpp \
    playermodeljsonextractor.cpp \
    playersjsondb.cpp \
    pointdartscontroller.cpp \
    pointlogisticcontroller.cpp \
    remotemodelscontext.cpp \
    scoredartscontroller.cpp \
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
    abstractdartscontrollerbuilder.h \
    abstractdartspointcontroller.h \
    abstractdartsscorecontroller.h \
    abstractmodelsservice.h \
    assembledartsscorefromjson.h\
    assemblejsondartsindexes.h \
    assemblejsonfromdartstournament.h \
    assemblejsonfromordereddartspointmodels.h \
    assembleplayerindexesfromjson.h \
    connectdartspointcontroller.h \
    connectdartsscorecontroller.h \
    dartscontrollerbuilder.h \
    dartsmodelsservice.h \
    dartsmultipointdatamodel.h \
    dartsmultiscoredatamodel.h \
    dartspointdbservice.h \
    dartsscorejsonassemblerservice.h \
    dartsscoresjsonassemblerservice.h \
    getordereddartspointmodels.h \
    ibinaryservice.h \
    idartsmodelsservice.h \
    idartspointdb.h \
    idartstournamentdb.h \
    ipersistence.h \
    iplayermodelsservice.h \
    iternaryservice.h \
    iunaryservice.h \
    jsonarrayfromdartspoints.h \
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
    dartsinputjsonassembler.h \
    dartsinputjsonextractor.h \
    dartspointinput.h \
    dartsscorecontroller.h \
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
    iplayerbuildercontext.h \
    iplayerinput.h \
    iplayerjsonassemblerservice.h \
    iplayerjsonextractorservice.h \
    iplayermodel.h \
    iplayermodelbuilder.h \
    ipointvalidator.h \
    iresponseinterface.h \
    iscorecontroller.h \
    iscoreparameter.h \
    iscorevalidator.h \
    itournament.h \
    itournamentbuilder.h \
    itournamentparameter.h \
    iurlparser.h \
    jsonextractor.h \
    localcricketcontroller.h \
    localplayermodelscontext.h \
    networkmanager.h \
    playerjsonassembler.h \
    playermodel.h \
    playermodelbuilder.h \
    playermodelbuildercontext.h \
    playermodeljsonextractor.h \
    playersjsondb.h \
    pointScoreCalculator.h \
    pointdartscontroller.h \
    pointlogisticcontroller.h \
    pointvalidator.h \
    remotemodelscontext.h \
    replytimeout.h \
    scoreCalculatorInterface.h \
    scorecalculator.h \
    scoredartscontroller.h \
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
