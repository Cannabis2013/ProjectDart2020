QT -= gui

TEMPLATE = lib
DEFINES += DARTSSTATISTICSFACTORY_LIBRARY


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Injectors/createsnapshotsprovider.cpp \
    Injectors/createstatisticprovider.cpp \
    Injectors/createstatsservices.cpp \
    Injectors/injectstatsroutines.cpp \
    Inputs/createinput.cpp \
    Inputs/inputsdb.cpp \
    Inputs/jsontosnapshot.cpp \
    Players/createstatmodel.cpp \
    Players/jsontostatsmodel.cpp \
    Players/statsmemory.cpp \
    Routines/bytearraytoinputs.cpp \
    Routines/createstatsreport.cpp \
    Routines/removeinputfromcontext.cpp \
    Routines/resetstatscontext.cpp \
    Routines/updatestatsmirror.cpp \
    Statistics/calculatemiddlevalue.cpp \
    Statistics/updatescorerange.cpp \
    createdartsstatistics.cpp
HEADERS += \
    Injectors/createsnapshotsprovider.h \
    Injectors/createstatisticprovider.h \
    Injectors/createstatsservices.h \
    Injectors/injectstatsroutines.h \
    Inputs/createinput.h \
    Inputs/inputsdb.h \
    Inputs/jsontosnapshot.h \
    Players/createstatmodel.h \
    Players/jsontostatsmodel.h \
    Players/statsmemory.h \
    Routines/bytearraytoinputs.h \
    Routines/createstatsreport.h \
    Routines/removeinputfromcontext.h \
    Routines/resetstatscontext.h \
    Routines/updatestatsmirror.h \
    Statistics/calculatemiddlevalue.h \
    Statistics/updatescorerange.h \
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
