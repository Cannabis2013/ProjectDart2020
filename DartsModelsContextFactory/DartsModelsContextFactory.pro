QT -= gui

TEMPLATE = lib
DEFINES += DartsMdFactLib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IndexesServices/dartsidxbuilder.cpp \
    InputServices/dartsinputstojson.cpp \
    TournamentServices/dartsmetamodelbuilder.cpp \
    TournamentServices/dartwinnermodelbuilder.cpp \
    createdartscontext.cpp

HEADERS += \
    ../DartsControllerFactory/ConverterServices/dcidxconverter.h \
    DbServices/loadfromstorage.h \
    DbServices/persistdbctx.h \
    FileIOServices/filejsonio.h \
    IndexesDbServices/dartsindex.h \
    IndexesServices/dartsidxbuilder.h \
    IndexesServices/updatedartsindexes.h \
    InputServices/countdartsinputs.h \
    InputServices/createdartsinputvalues.h \
    InputServices/dartsinput.h \
    InputServices/dartsinputbuilder.h \
    InputServices/dartsinputstojson.h \
    InputServices/dartsiptsdbctx.h \
    InputServices/getdartsinputs.h \
    InputServices/removedartsinputs.h \
    InputServices/sortdartsinputs.h \
    InputServices/sortdartsinputsbyindexes.h \
    TournamentServices/GetDartsTournamentIds.h \
    TournamentServices/dartsbuilder.h \
    TournamentServices/dartsmetamodelbuilder.h \
    TournamentServices/dartstournamentrepair.h \
    TournamentServices/dartsverifyconsistency.h \
    TournamentServices/dartwinnermodelbuilder.h \
    TournamentServices/getdartstournamentfromdb.h \
    TournamentServices/jsontodartsmodels.h \
    TournamentServices/resetdartstournament.h \
    TournamentServices/setdartsplayerdetails.h \
    TournamentsDbServices/dartsdbcontext.h \
    TournamentsDbServices/dartsjsonbuilder.h \
    createdartscontext.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_armeabi-v7a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_armeabi-v7a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_armeabi-v7a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/release/ -lDartsModelsContext_armeabi-v7a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/debug/ -lDartsModelsContext_armeabi-v7a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext_armeabi-v7a
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
