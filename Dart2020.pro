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
        ftpdatamodel.cpp \
        ftpscorecontroller.cpp \
        localftpcontroller.cpp \
        localplayerdbcontext.cpp \
        localplayermodelscontext.cpp \
        localtournamentmodeldb.cpp \
        localtournamentmodelscontext.cpp \
        main.cpp \
        modelscontextinterface.cpp \
        pointlogisticmanager.cpp \
        scoreindexcontroller.cpp

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
    abstractmodelscontextinterface.h \
    abstractpersistence.h \
    dartapplication.h \
    ftpdatamodel.h \
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
    localftpcontroller.h \
    localplayerdbcontext.h \
    localplayermodelscontext.h \
    localtournamentmodeldb.h \
    localtournamentmodelscontext.h \
    logisticmanagerinterface.h \
    modelbuildercontext.h \
    modelinterface.h \
    modelscontextinterface.h \
    persistenceinterface.h \
    player.h \
    playermodelbuilder.h \
    playermodelbuildercontext.h \
    playermodelscontextinterface.h \
    pointScoreCalculator.h \
    pointlogisticmanager.h \
    pointvalidator.h \
    score.h \
    scoreCalculatorInterface.h \
    scorecalculator.h \
    scoreindexcontroller.h \
    tournamentmodelbuilder.h \
    tournamentmodelscontextinterface.h \
    userscorescontrollerinterface.h

DISTFILES += \

#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll
#LIBS += $$PWD/SSL/libssl-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
