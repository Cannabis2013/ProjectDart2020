QT -= gui

TEMPLATE = lib
DEFINES += DartsMdFactLib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DbServices/loadfromstorage.cpp \
    DbServices/savetostorage.cpp \
    FileIOServices/filejsonio.cpp \
    IndexesServices/dartsindexbuilder.cpp \
    Injectors/dartsindexinjector.cpp \
    Injectors/dartsinputinjector.cpp \
    Injectors/dartsplayerinjector.cpp \
    Injectors/dartstournamentinjector.cpp \
    Injectors/injectdartsroutines.cpp \
    InputServices/dartsinputdb.cpp \
    Routines/dartsaddinputtodb.cpp \
    Routines/dartsdisplayplayerinput.cpp \
    Routines/dartshideplayerinput.cpp \
    InputServices/dartsinputconverter.cpp \
    InputServices/dartsinputstobytearray.cpp \
    Routines/dartsinputtojson.cpp \
    InputServices/getdartsinputs.cpp \
    InputServices/removedartsinputs.cpp \
    PlayerServices/dartsconvertplayer.cpp \
    Routines/addtournamenttodb.cpp \
    Routines/gettournamentsasjson.cpp \
    TournamentServices/dartsbuilder.cpp \
    TournamentServices/dartsjsonconverter.cpp \
    TournamentServices/dartsmetamodelbuilder.cpp \
    Routines/dartsresettournament.cpp \
    TournamentServices/dartssetwinner.cpp \
    Routines/dartstournamentrepair.cpp \
    TournamentServices/dartsverifyconsistency.cpp \
    TournamentServices/dartwinnermodelbuilder.cpp \
    Routines/removetournamentsfromdb.cpp \
    TournamentsDbServices/dartsdbcontext.cpp \
    Routines/gettournamentasjson.cpp \
    createdartscontext.cpp

HEADERS += \
    DbServices/loadfromstorage.h \
    DbServices/savetostorage.h \
    FileIOServices/filejsonio.h \
    IndexesDbServices/dartsindex.h \
    IndexesServices/dartsindexbuilder.h \
    Injectors/dartsindexinjector.h \
    Injectors/dartsinputinjector.h \
    Injectors/dartsplayerinjector.h \
    Injectors/dartstournamentinjector.h \
    Injectors/injectdartsroutines.h \
    InputServices/countdartsinputs.h \
    InputServices/dartsinputdb.h \
    Routines/dartsaddinputtodb.h \
    Routines/dartsdisplayplayerinput.h \
    Routines/dartshideplayerinput.h \
    InputServices/dartsinput.h \
    InputServices/dartsinputbuilder.h \
    InputServices/dartsinputconverter.h \
    InputServices/dartsinputstobytearray.h \
    Routines/dartsinputtojson.h \
    InputServices/getdartsinputs.h \
    InputServices/removedartsinputs.h \
    InputServices/sortdartsinputs.h \
    InputServices/sortdartsinputsbyindexes.h \
    PlayerServices/dartsconvertplayer.h \
    Routines/addtournamenttodb.h \
    Routines/gettournamentsasjson.h \
    TournamentServices/GetDartsTournamentIds.h \
    TournamentServices/dartsbuilder.h \
    TournamentServices/dartsjsonconverter.h \
    TournamentServices/dartsmetamodelbuilder.h \
    Routines/dartsresettournament.h \
    TournamentServices/dartssetwinner.h \
    Routines/dartstournamentrepair.h \
    TournamentServices/dartsverifyconsistency.h \
    TournamentServices/dartwinnermodelbuilder.h \
    TournamentServices/getdartstournamentfromdb.h \
    Routines/removetournamentsfromdb.h \
    TournamentsDbServices/dartsdbcontext.h \
    Routines/gettournamentasjson.h \
    createdartscontext.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/release/ -lDartsModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/debug/ -lDartsModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext_arm64-v8a
}
!android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/release/ -lDartsModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/debug/ -lDartsModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext
}

INCLUDEPATH += $$PWD/../DartsModelsContext
DEPENDPATH += $$PWD/../DartsModelsContext
INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
