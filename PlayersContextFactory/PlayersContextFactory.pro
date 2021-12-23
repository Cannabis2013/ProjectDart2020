QT -= gui

TEMPLATE = lib

DEFINES += PlaFactLib

HEADERS += \
    DataServices/plajsonbuilder.h \
    DbServices/isaveplayers.h \
    DbServices/loadplayermodels.h \
    DbServices/playersdbcontext.h \
    DbServices/saveplayermodels.h \
    IOServices/filejsonio.h \
    ModelsServices/duplicatechecker.h \
    Services/getplayersfromdb.h \
    Services/plabuilder.h \
    Services/playermodel.h \
    createplayerscontext.h

SOURCES += \
    DataServices/plajsonbuilder.cpp \
    DbServices/loadplayermodels.cpp \
    DbServices/playersdbcontext.cpp \
    DbServices/saveplayermodels.cpp \
    IOServices/filejsonio.cpp \
    ModelsServices/duplicatechecker.cpp \
    Services/getplayersfromdb.cpp \
    Services/plabuilder.cpp \
    createplayerscontext.cpp

android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
}

!android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
}

INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
