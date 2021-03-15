QT += quick

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
        abstractjsonpersistence.cpp \
        dartapplication.cpp \
    defaultmodelsdbcontext.cpp \
        ftpdatamodel.cpp \
        ftpscorecontroller.cpp \
        iurlparser.cpp \
        localftpcontroller.cpp \
    localmodelscontext.cpp \
        localplayerdbcontext.cpp \
        localplayermodelscontext.cpp \
        localtournamentmodelscontext.cpp \
        main.cpp \
        networkmanager.cpp \
        pointlogisticcontroller.cpp \
    remotemodelscontext.cpp \
        scoreindexcontroller.cpp \
        scorelogisticcontroller.cpp \
        sftpdatamodel.cpp \
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
    AbstractApplicationInterface.h \
    IControllerBuilder.h \
    LinkedList.h \
    PointIndexController.h \
    ScoreValidator.h \
    abstractcontrollerbuilder.h \
    abstractgamecontroller.h \
    abstractjsonpersistence.h \
    abstractmodelscontext.h \
    abstractpersistence.h \
    dartapplication.h \
    defaultmodelsdbcontext.h \
    firsttopostscore.h \
    ftpdatamodel.h \
    ftplogisticcontrollerinterface.h \
    ftpmodelbuilder.h \
    ftpscorecontroller.h \
    ftptournament.h \
    ftptournamentmodelinterface.h \
    gamecontrollerbuilder.h \
    idatacontext.h \
    imodelsdbcontext.h \
    indexcontrollerinterface.h \
    inputvalidatorinterface.h \
    iplayerbuildercontext.h \
    iplayercontext.h \
    iplayermodel.h \
    iplayermodelbuilder.h \
    iresponseinterface.h \
    iscoremodel.h \
    itournamentmodelbuilder.h \
    iurlparser.h \
    localftpcontroller.h \
    localmodelscontext.h \
    localplayerdbcontext.h \
    localplayermodelscontext.h \
    localtournamentmodelscontext.h \
    modelbuildercontext.h \
    modelinterface.h \
    networkmanager.h \
    persistenceinterface.h \
    player.h \
    playermodelbuilder.h \
    playermodelbuildercontext.h \
    playermodelscontextinterface.h \
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
    tournamentmodelscontextinterface.h \
    urlparser.h \
    userscorescontrollerinterface.h

DISTFILES += \

#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll
#LIBS += $$PWD/SSL/libssl-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
