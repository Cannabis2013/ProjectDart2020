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
    IndexesServices/dartsindexbuilder.cpp \
    IndexesServices/updatedartsindexes.cpp \
    Injectors/dartsindexinjector.cpp \
    Injectors/dartsinputinjector.cpp \
    Injectors/dartsplayerinjector.cpp \
    Injectors/dartstournamentinjector.cpp \
    Injectors/injectdartsroutines.cpp \
    Injectors/localpersistenceinjector.cpp \
    InputServices/dartsaddinputtodb.cpp \
    InputServices/dartsdbinputstojson.cpp \
    InputServices/dartsinputconverter.cpp \
    InputServices/dartsinputstojson.cpp \
    InputServices/dartsinputtojson.cpp \
    InputServices/dartssetipthint.cpp \
    InputServices/getdartsinputs.cpp \
    InputServices/jsontodartsinputs.cpp \
    InputServices/removedartsinputs.cpp \
    PersistServices/dartspersist.cpp \
    PlayerServices/dartsconvertplayer.cpp \
    TournamentServices/dartsbuilder.cpp \
    TournamentServices/dartscreatetournament.cpp \
    TournamentServices/dartsjsonconverter.cpp \
    TournamentServices/dartsmetamodelbuilder.cpp \
    TournamentServices/dartsremovetournaments.cpp \
    TournamentServices/dartsresettournament.cpp \
    TournamentServices/dartssetwinner.cpp \
    TournamentServices/dartstournamentrepair.cpp \
    TournamentServices/dartsverifyconsistency.cpp \
    TournamentServices/dartwinnermodelbuilder.cpp \
    TournamentServices/jsontodartsmodels.cpp \
    TournamentsDbServices/dartsconverttojson.cpp \
    createdartscontext.cpp

HEADERS += \
    ../DartsControllerFactory/Index/dcidxconverter.h \
    DbServices/convertdartsmodels.h \
    DbServices/loadfromstorage.h \
    DbServices/savetostorage.h \
    FileIOServices/filejsonio.h \
    IndexesDbServices/dartsindex.h \
    IndexesServices/dartsindexbuilder.h \
    IndexesServices/updatedartsindexes.h \
    Injectors/dartsindexinjector.h \
    Injectors/dartsinputinjector.h \
    Injectors/dartsplayerinjector.h \
    Injectors/dartstournamentinjector.h \
    Injectors/injectdartsroutines.h \
    Injectors/localpersistenceinjector.h \
    InputServices/countdartsinputs.h \
    InputServices/dartsaddinputtodb.h \
    InputServices/dartsdbinputstojson.h \
    InputServices/dartsinput.h \
    InputServices/dartsinputbuilder.h \
    InputServices/dartsinputconverter.h \
    InputServices/dartsinputstojson.h \
    InputServices/dartsinputtojson.h \
    InputServices/dartsiptsdbctx.h \
    InputServices/dartssetipthint.h \
    InputServices/getdartsinputs.h \
    InputServices/jsontodartsinputs.h \
    InputServices/removedartsinputs.h \
    InputServices/sortdartsinputs.h \
    InputServices/sortdartsinputsbyindexes.h \
    PersistServices/dartspersist.h \
    PlayerServices/dartsconvertplayer.h \
    TournamentServices/GetDartsTournamentIds.h \
    TournamentServices/dartsbuilder.h \
    TournamentServices/dartscreatetournament.h \
    TournamentServices/dartsjsonconverter.h \
    TournamentServices/dartsmetamodelbuilder.h \
    TournamentServices/dartsremovetournaments.h \
    TournamentServices/dartsresettournament.h \
    TournamentServices/dartssetwinner.h \
    TournamentServices/dartstournamentrepair.h \
    TournamentServices/dartsverifyconsistency.h \
    TournamentServices/dartwinnermodelbuilder.h \
    TournamentServices/getdartstournamentfromdb.h \
    TournamentServices/jsontodartsmodels.h \
    TournamentsDbServices/dartsconverttojson.h \
    TournamentsDbServices/dartsdbcontext.h \
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
