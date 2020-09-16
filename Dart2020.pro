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
        applicationinterface.cpp \
        idatamodelbuilder.cpp \
        imodeldbcontext.cpp \
        localfirsttopost.cpp \
        localplayerdbcontext.cpp \
        localplayermodelscontext.cpp \
        localtournamentmodeldb.cpp \
        localtournamentmodelscontext.cpp \
        main.cpp \
        pointlogisticmanager.cpp \
        scoredatamodel.cpp

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
    IControllerBuilder.h \
    abstractgamecontroller.h \
    abstractjsonpersistence.h \
    abstractpersistence.h \
    abstractplayermodelscontext.h \
    abstracttournamentmodelscontext.h \
    applicationinterface.h \
    defaultplayerbuilderconfigurations.h \
    gamebuilder.h \
    idatacontext.h \
    idatamodelbuilder.h \
    imodel.h \
    imodeldbcontext.h \
    iplayerbuildercontext.h \
    iplayercontext.h \
    iplayermodel.h \
    ipointlogisticinterface.h \
    iresponseinterface.h \
    iroundmodel.h \
    iscoremodel.h \
    isetmodel.h \
    itournamentmodel.h \
    localfirsttopost.h \
    localplayerbuilder.h \
    localplayerdbcontext.h \
    localplayermodelscontext.h \
    localtournamentmodeldb.h \
    localtournamentmodelscontext.h \
    modelbuildercollection.h \
    modelbuildercontext.h \
    persistenceinterface.h \
    player.h \
    pointlogisticmanager.h \
    round.h \
    score.h \
    scoredatamodel.h \
    set.h \
    tournament.h

DISTFILES += \

#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll
#LIBS += $$PWD/SSL/libssl-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a
