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
    Inputs/Models/snapshot.h \
    Inputs/icreateinput.h \
    Inputs/ijsontosnapshot.h \
    Inputs/snapshotsservices.h \
    Players/ICreateStatModel.h \
    Players/Models/imirrorsdb.h \
    Players/ijsontostatsmodel.h \
    Players/statisticservices.h \
    Report/icreatereport.h \
    Routines/IAddStatsToPlayer.h \
    SLAs/servicescontext.h \
    StatsServices/CalcAverage/ICalcAverage.h \
    Db/istatsdb.h \
    Routines/IJsonToModels.h \
    Routines/iaddplayerstomem.h \
    Routines/iresetmodels.h \
    SLAs/idartsstatistics.h \
    Routines/routineservices.h \
    StatsServices/ScoreRange/iupdatescorerange.h \
    StatsServices/StatsServices.h \
    dartsstatistics.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
