TEMPLATE = lib
QT -= gui
DEFINES += DartsCtxLib

HEADERS += \
    ByteArrayServices/converttobytearray.h \
    DbSLAs/abstractloadmodels.h \
    DbSLAs/abstractsavetostorage.h \
    DbSLAs/iconvertfromdata.h \
    DbSLAs/idartspersist.h \
    DbSLAs/idbcontext.h \
    DbSLAs/idbjsonbuilder.h \
    DbSLAs/imodelconverter.h \
    FileIOSLAs/ifiledataio.h \
    ForeignContextSLAs/DartsPlayerServices.h \
    ForeignContextSLAs/IDartsConvertPlayer.h \
    IndexesDbSLAs/idartsindex.h \
    IndexesSLAs/dartsindexservices.h \
    IndexesSLAs/idartsidxbuilder.h \
    IndexesSLAs/idcidxbuilder.h \
    IndexesSLAs/iupdatedartsindexes.h \
    InputModelsSLAs/idartsinput.h \
    InputModelsSLAs/idartsinputstojson.h \
    InputModelsSLAs/iplayerinput.h \
    InputSLAs/IDartsSetIptHint.h \
    InputSLAs/dartsinputservices.h \
    InputSLAs/icountinputmodels.h \
    InputSLAs/idartsaddinputtodb.h \
    InputSLAs/idartsinputtojson.h \
    InputSLAs/isortinputmodels.h \
    InputsDbSLAs/idartsinputbuilder.h \
    InputsDbSLAs/igetinputs.h \
    InputsDbSLAs/iremovedartsinputs.h \
    ModelSLAs/imodel.h \
    Models/DartsPlayer.h \
    PredicateSLAs/imodelpredicate.h \
    SLAs/absdartsctx.h \
    SLAs/dartsmodelsservices.h \
    TournamentModels/dartsmetamodel.h \
    TournamentModels/dartstournament.h \
    TournamentModelsSLAs/idartstournament.h \
    TournamentsDbSLAs/idartsbuilder.h \
    TournamentsDbSLAs/igetdartstournament.h \
    TournamentsDbSLAs/itournamentjsonbuilder.h \
    TournamentsDbSLAs/persistenceservices.h \
    TournamentsSLAs/IDartsRemoveTournaments.h \
    TournamentsSLAs/IDartsSetWinner.h \
    TournamentsSLAs/dartsservices.h \
    TournamentsSLAs/idartsconsistency.h \
    TournamentsSLAs/idartscreatemeta.h \
    TournamentsSLAs/idartscreatetournament.h \
    TournamentsSLAs/idartsresettournament.h \
    TournamentsSLAs/idmcaddindexestotournament.h \
    TournamentsSLAs/igettournamentids.h \
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
