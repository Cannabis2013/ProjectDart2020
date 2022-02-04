TEMPLATE = subdirs

SUBDIRS += \
    DartApp \
    DartsController \
    DartsControllerFactory\
    DartsModelsContext \
    DartsModelsContextFactory \
    DartsStatistics \
    DartsStatisticsFactory \
    PlayerModelsContext \
    PlayersContextFactory

DartsStatisticsFactory.depends = DartsStatistics
PlayersContextFactory.depends = PlayerModelsContext
DartsController.depends = DartsModelsContext
DartsControllerFactory.depends = DartsController DartsModelsContext
DartsModelsContext.depends = PlayerModelsContext
DartsModelsContextFactory.depends = PlayerModelsContext DartsModelsContext
DartApp.depends = PlayerModelsContext PlayersContextFactory DartsModelsContext DartsModelsContextFactory DartsController DartsControllerFactory DartsStatistics DartsStatisticsFactory
