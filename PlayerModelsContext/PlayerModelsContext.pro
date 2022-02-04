TEMPLATE = lib
QT -= gui
DEFINES += PlaCtxLib

HEADERS += \
    DataSLAs/ijsonbuilder.h \
    DbSLAs/IPlayersDbContext.h \
    DbSLAs/PlayersDbSLAs.h \
    DbSLAs/ifetchdb.h \
    DbSLAs/igetplayerfromdb.h \
    DbSLAs/iplayer.h \
    DbSLAs/iplayerbuilder.h \
    DbSLAs/isaveplayers.h \
    IOSLAs/ifiledataio.h \
    ModelsSLAs/iduplicatechecker.h \
    ContextSLA/absplactx.h \
    playerscontext.h

SOURCES += \
    playerscontext.cpp
