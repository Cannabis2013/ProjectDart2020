QT -= gui

TEMPLATE = lib
DEFINES += DARTSSTATISTICS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dartsstatistics.cpp

HEADERS += \
    InputRoutines/IRemoveInputFromDb.h \
    Inputs/icreateinput.h \
    Report/icreatereport.h \
    Report/reportservices.h \
    Routines/IAddStatsToPlayer.h \
    Routines/igetplayer.h \
    StatsServices/CalcAverage/ICalcAverage.h \
    Db/istatsdb.h \
    Inputs/ijsontoinput.h \
    Routines/IJsonToModels.h \
    Players/ijsontoplayer.h \
    Players/Models/playerstat.h \
    Routines/iaddplayerstomem.h \
    Routines/iresetmodels.h \
    SLAs/idartsstatistics.h \
    Inputs/inputservices.h \
    Players/playerservices.h \
    Routines/routineservices.h \
    SLAs/servicesprovider.h \
    StatsServices/StatsServices.h \
    dartsstatistics.h \
    Inputs/Models/input.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
