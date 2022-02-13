QT -= gui

TEMPLATE = lib
DEFINES += DARTSCONTROLLERLIB

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dartscontroller.cpp

HEADERS += \
    ControllerSLA/idartsctrl.h \
    DCFinishesSLAs/dartsconstructslas.h \
    DCFinishesSLAs/dcfinishesservices.h \
    DCFinishesSLAs/idartsattemptsservice.h \
    DCFinishesSLAs/idartsboundaries.h \
    DCFinishesSLAs/idartscreatefinishes.h \
    DCFinishesSLAs/idartsdivisorvalues.h \
    DCFinishesSLAs/idartsfieldvalues.h \
    DCFinishesSLAs/idartsfinishesdb.h \
    DCFinishesSLAs/idartsmodidentifiers.h \
    DCFinishesSLAs/idartsterminaldivisor.h \
    DCFinishesSLAs/idartsthresholds.h \
    DCFinishesSLAs/idcfinishbuilder.h \
    DCIndexSLAs/dcindexservices.h \
    DCIndexSLAs/idcindexcontroller.h \
    DCIndexSLAs/idcindextobytearray.h \
    DCInputSLAs/dcinputsservices.h \
    DCInputSLAs/idcinputadder.h \
    DCInputSLAs/idcinputbuilder.h \
    DCInputSLAs/idcinputevaluator.h \
    DCJsonSLAs/dcjsonservices.h \
    DCMetaSLAs/dcmetaservices.h \
    DCMetaSLAs/idcmetabuilder.h \
    DCMetaSLAs/idcmetaconverter.h \
    DCMetaSLAs/idcmetamanager.h \
    DCScoresSLAs/dcplayersservices.h \
    DCScoresSLAs/idcplayermanager.h \
    DCTurnValuesSLAs/dcturnvaluesservices.h \
    DCTurnValuesSLAs/idccreateturnvalues.h \
    ModelBuilderSLAs/idcjsontomodel.h \
    ModelBuilderSLAs/idcmodeltojson.h \
    ModelsConverterSLAs/idcjsontomodels.h \
    Routines/idcinitialize.h \
    Models/dcindex.h \
    DCJsonSLAs/AbstractDCJsonBuilder.h \
    DCJsonSLAs/dcjsonbuilderservices.h \
    DCJsonSLAs/idcmodeljsonbuilder.h \
    Models/dcinput.h \
    Models/dcmeta.h \
    Models/dcplayer.h \
    Models/dcturnvalues.h \
    Routines/idcaddtomdsctx.h \
    Routines/dcroutines.h \
    Routines/idcredoturn.h \
    Routines/idcresetservices.h \
    Routines/idcundoturn.h \
    ServicesProvider/dcservices.h \
    dartscontroller.h

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
