QT -= gui

TEMPLATE = lib
DEFINES += DARTSCONTROLLERLIB

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/dartscontroller.cpp

HEADERS += \
    Controller/idartsctrl.h \
    Finishes/dartsconstructslas.h \
    Finishes/dcfinishesservices.h \
    Finishes/idartsattemptsservice.h \
    Finishes/idartsboundaries.h \
    Finishes/idartscreatefinishes.h \
    Finishes/idartsdivisorvalues.h \
    Finishes/idartsfieldvalues.h \
    Finishes/idartsfinishesdb.h \
    Finishes/idartsmodidentifiers.h \
    Finishes/idartsterminaldivisor.h \
    Finishes/idartsthresholds.h \
    Finishes/idcfinishbuilder.h \
    Index/dcindexservices.h \
    Index/idcindexcontroller.h \
    Inputs/dcinputsservices.h \
    Inputs/idcinputadder.h \
    Inputs/idcinputbuilder.h \
    Inputs/idcinputconverter.h \
    Inputs/idcinputevaluator.h \
    Meta/dcmetaservices.h \
    Meta/idcmetabuilder.h \
    Meta/idcmetaconverter.h \
    Meta/idcmetamanager.h \
    Players/dcplayersservices.h \
    Players/idcplayermanager.h \
    Converters/idcjsontomodel.h \
    Converters/idcmodeltojson.h \
    Converters/idcjsontomodels.h \
    Routines/dartscontrollerroutines.h \
    Routines/idcaddinput.h \
    Routines/idccreatewinnerjson.h \
    Routines/idcgetscoresasjson.h \
    Routines/idcgetturnvaluesasjson.h \
    Routines/idcinitialize.h \
    Models/dcindex.h \
    Models/dcinput.h \
    Models/dcmeta.h \
    Models/dcplayer.h \
    Routines/idcredoturn.h \
    Routines/idcresetservices.h \
    Routines/idcundoturn.h \
    ServicesProvider/dcservices.h \
    Controller/dartscontroller.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

!android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext
}

android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext_arm64-v8a
}

INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
INCLUDEPATH += $$PWD/../DartsModelsContext
DEPENDPATH += $$PWD/../DartsModelsContext
