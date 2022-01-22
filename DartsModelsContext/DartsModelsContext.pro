TEMPLATE = lib
QT -= gui
DEFINES += DartsCtxLib

HEADERS += \
    ByteArrayServices/converttobytearray.h \
    DbSLAs/abstractloadmodels.h \
    DbSLAs/abstractsavetostorage.h \
    DbSLAs/iconvertfromdata.h \
    DbSLAs/idbcontext.h \
    DbSLAs/idbjsonbuilder.h \
    DbSLAs/imodelconverter.h \
    FileIOSLAs/ifiledataio.h \
    IndexesDbSLAs/idartsindex.h \
    IndexesSLAs/dartsindexslas.h \
    IndexesSLAs/idartsidxbuilder.h \
    IndexesSLAs/idcidxbuilder.h \
    IndexesSLAs/iupdatedartsindexes.h \
    InputModels/dartsinputstats.h \
    InputModelsSLAs/idartsinput.h \
    InputModelsSLAs/idartsinputstats.h \
    InputModelsSLAs/idartsinputstojson.h \
    InputModelsSLAs/iplayerinput.h \
    InputSLAs/IDartsSetIptHint.h \
    InputSLAs/dartsiptslas.h \
    InputSLAs/icountinputmodels.h \
    InputSLAs/isortinputmodels.h \
    InputsDbSLAs/idartsinputbuilder.h \
    InputsDbSLAs/igetinputs.h \
    InputsDbSLAs/iremovedartsinputs.h \
    ModelSLAs/imodel.h \
    PredicateSLAs/imodelpredicate.h \
    SLAs/absdartsctx.h \
    TournamentModels/dartsmetamodel.h \
    TournamentModels/dartstournament.h \
    TournamentModelsSLAs/idartstournament.h \
    TournamentsDbSLAs/idartsbuilder.h \
    TournamentsDbSLAs/igetdartstournament.h \
    TournamentsDbSLAs/itournamentjsonbuilder.h \
    TournamentsDbSLAs/persistenceslas.h \
    TournamentsSLAs/IDartsSetWinner.h \
    TournamentsSLAs/dartsslas.h \
    TournamentsSLAs/idartsconsistency.h \
    TournamentsSLAs/idartscreatemeta.h \
    TournamentsSLAs/idmcaddindexestotournament.h \
    TournamentsSLAs/igettournamentids.h \
    TournamentsSLAs/iresetdartstournament.h \
    TournamentsSLAs/isettournamentplayerdetails.h \
    TournamentsSLAs/itournamentrepair.h \
    TournamentsSLAs/iwinnerinfobuilder.h \
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
