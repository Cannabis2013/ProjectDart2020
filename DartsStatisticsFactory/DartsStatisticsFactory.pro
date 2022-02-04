QT -= gui

TEMPLATE = lib
DEFINES += DARTSSTATISTICSFACTORY_LIBRARY


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Injectors/injectinputservices.cpp \
    Injectors/injectplayerservices.cpp \
    Inputs/createinput.cpp \
    Inputs/inputsdb.cpp \
    Inputs/jsontoinput.cpp \
    Players/jsontoplayer.cpp \
    Players/playersdb.cpp \
    createdartsstatistics.cpp

HEADERS += \
    Injectors/injectinputservices.h \
    Injectors/injectplayerservices.h \
    Inputs/createinput.h \
    Inputs/inputsdb.h \
    Inputs/jsontoinput.h \
    Players/jsontoplayer.h \
    Players/playersdb.h \
    createdartsstatistics.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/release/ -lDartsStatistics_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/debug/ -lDartsStatistics_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatistics/ -lDartsStatistics_arm64-v8a
}
!android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/release/ -lDartsStatistics
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/debug/ -lDartsStatistics
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatistics/ -lDartsStatistics
}

INCLUDEPATH += $$PWD/../DartsStatistics
DEPENDPATH += $$PWD/../DartsStatistics
