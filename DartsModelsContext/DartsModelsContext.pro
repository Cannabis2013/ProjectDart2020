TEMPLATE = lib
QT -= gui
DEFINES += DartsCtxLib

HEADERS += \
    DbSLAs/abstractloadmodels.h \
    DbSLAs/abstractsavetostorage.h \
    DbSLAs/iconverttomodels.h \
    DbSLAs/idbcontext.h \
    DbSLAs/imodelconverter.h \
    FileIOSLAs/ifiledataio.h \
    IndexesDbSLAs/idartsindex.h \
    IndexesSLAs/dartsindexslas.h \
    IndexesSLAs/idartsidxbuilder.h \
    IndexesSLAs/idcidxbuilder.h \
    IndexesSLAs/iupdatedartsindexes.h \
    InputModels/dartsinputstats.h \
    InputModels/diptvals.h \
    InputModelsSLAs/abstractdartsinput.h \
    InputModelsSLAs/idartsinputstats.h \
    InputModelsSLAs/iplayerinput.h \
    InputSLAs/dartsiptslas.h \
    InputSLAs/icountinputmodels.h \
    InputSLAs/icreatemodelvalues.h \
    InputSLAs/isortinputmodels.h \
    InputsDbSLAs/DartsiptDbSLAs.h \
    InputsDbSLAs/idartsinputbuilder.h \
    InputsDbSLAs/igetinputs.h \
    InputsDbSLAs/iremovedartsinputs.h \
    ModelSLAs/imodel.h \
    PredicateSLAs/imodelpredicate.h \
    SLAs/absdartsctx.h \
    TournamentModels/dartsmetamodel.h \
    TournamentModels/dartstournament.h \
    TournamentModels/tnmvalues.h \
    TournamentModelsSLAs/idartstournament.h \
    TournamentsDbSLAs/dartsdbslas.h \
    TournamentsDbSLAs/idartsbuilder.h \
    TournamentsDbSLAs/igetdartstournament.h \
    TournamentsDbSLAs/itournamentjsonbuilder.h \
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
    dartscontext.cpp


android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_armeabi-v7a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_armeabi-v7a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_armeabi-v7a
}
!android{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
}

INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
