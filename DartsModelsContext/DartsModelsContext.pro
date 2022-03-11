TEMPLATE = lib
QT -= gui
DEFINES += DartsCtxLib

HEADERS += \
    ByteArrayServices/converttobytearray.h \
    DbSLAs/idbcontext.h \
    DbSLAs/imodelconverter.h \
    FileIOSLAs/ifiledataio.h \
    ForeignContextSLAs/DartsPlayerServices.h \
    ForeignContextSLAs/IDartsConvertPlayer.h \
    IndexesDbSLAs/idartsindex.h \
    IndexesSLAs/dartsindexservices.h \
    IndexesSLAs/idartsidxbuilder.h \
    InputModelsSLAs/idartsinput.h \
    Persistence/ipersistence.h \
    Routines/IDartsHideInput.h \
    Routines/idartsinputstojson.h \
    InputModelsSLAs/iplayerinput.h \
    InputSLAs/dartsinputservices.h \
    InputSLAs/icountinputmodels.h \
    Routines/idartsaddinputtodb.h \
    Routines/idartsinputtojson.h \
    InputSLAs/isortinputmodels.h \
    InputsDbSLAs/idartsinputbuilder.h \
    InputsDbSLAs/igetinputs.h \
    InputsDbSLAs/iremovedartsinputs.h \
    ModelSLAs/imodel.h \
    Models/DartsPlayer.h \
    PredicateSLAs/imodelpredicate.h \
    Routines/IDartsAddTournament.h \
    Routines/idartsrevealinput.h \
    Routines/igettournamentsasjson.h \
    SLAs/absdartsctx.h \
    SLAs/dartsmodelsroutines.h \
    SLAs/dartsmodelsservices.h \
    TournamentModels/dartsmetamodel.h \
    TournamentModels/dartstournament.h \
    TournamentModelsSLAs/idartstournament.h \
    TournamentsDbSLAs/idartsbuilder.h \
    TournamentsDbSLAs/igetdartstournament.h \
    Routines/IDartsSetWinner.h \
    Routines/igettournamentasjson.h \
    TournamentsSLAs/idartsconsistency.h \
    TournamentsSLAs/idartscreatemeta.h \
    Routines/idartsremovetournaments.h \
    Routines/idartsresettournament.h \
    TournamentsSLAs/idmcaddindexestotournament.h \
    TournamentsSLAs/igettournamentids.h \
    Routines/itournamentrepair.h \
    TournamentsSLAs/iwinnerinfobuilder.h \
    TournamentsSLAs/tournamentservices.h \
    dartscontext.h

SOURCES += \
    ByteArrayServices/converttobytearray.cpp \
    dartscontext.cpp


android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
}
!android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
}

INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
