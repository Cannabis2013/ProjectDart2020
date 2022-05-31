QT -= gui
TEMPLATE = lib
DEFINES += DCFactLib

HEADERS += \
    Index/dcindexconverter.h \
    Finishes/dartsboundaries.h \
    Finishes/dartscreatefinishes.h \
    Finishes/dartsdefaultattempts.h \
    Finishes/dartsdivisors.h \
    Finishes/dartsfieldvalues.h \
    Finishes/dartsmodidentifiers.h \
    Finishes/dartsterminaldivisor.h \
    Finishes/dcfinishbuilder.h \
    Finishes/dclogisticdb.h \
    Finishes/defaultthresholds.h \
    Inputs/dcinputconverter.h \
    Players/dcplayertojson.h \
    Inputs/dcinputbuilder.h \
    Inputs/dcjsontoinputmodels.h \
    Meta/dcmetabuilder.h \
    Meta/dcmetaconverter.h \
    Meta/dcmetaservice.h \
    Meta/dcsettournamentid.h \
    Players/dcconvertplayers.h \
    Players/dcplayerbuilder.h \
    Players/dpcplayerscontext.h \
    Players/dscplayerscontext.h \
    Inputs/dpcinputadder.h \
    Inputs/dpcinputevaluator.h \
    Inputs/dscinputadder.h \
    Inputs/dscinputevaluator.h \
    DartsAssemblers/assembledpc.h \
    DartsAssemblers/assembledsc.h \
    Index/dpcindexcontroller.h \
    Index/dscindexcontroller.h \
    Init/dcinitialize.h \
    Injectors/dcinjectfinclient.h \
    Injectors/dcinjectmetaclient.h \
    Injectors/dpcinjectidxservices.h \
    Injectors/dpcinjectiptservices.h \
    Injectors/dpcinjectplaservices.h \
    Injectors/dscindexinjector.h \
    Injectors/dscinjectplaservives.h \
    Injectors/dscinputinjector.h \
    Injectors/injectdpcroutines.h \
    Injectors/injectdscroutines.h \
    Routines/dcaddinput.h \
    Routines/dccreatewinnerreport.h \
    Routines/dcgetscoresasjson.h \
    Routines/dcgetturnvaluesasjson.h \
    Routines/dcredoturn.h \
    Routines/dcresetservices.h \
    Routines/dcundoturn.h \
    ControllerBuilder/createdartscontroller.h
SOURCES += \
    Finishes/dartscreatefinishes.cpp \
    Finishes/dcfinishbuilder.cpp \
    Finishes/defaultthresholds.cpp \
    Index/dcindexconverter.cpp \
    Index/dscindexcontroller.cpp \
    Inputs/dcinputbuilder.cpp \
    Inputs/dcinputconverter.cpp \
    Inputs/dcjsontoinputmodels.cpp \
    Inputs/dpcinputadder.cpp \
    Meta/dcmetabuilder.cpp \
    Meta/dcmetaconverter.cpp \
    Players/dcconvertplayers.cpp \
    Players/dcplayerbuilder.cpp \
    Players/dcplayertojson.cpp \
    Players/dpcplayerscontext.cpp \
    Players/dscplayerscontext.cpp \
    Inputs/dpcinputevaluator.cpp \
    Inputs/dscinputevaluator.cpp \
    DartsAssemblers/assembledpc.cpp \
    DartsAssemblers/assembledsc.cpp \
    Index/dpcindexcontroller.cpp \
    Init/dcinitialize.cpp \
    Injectors/dcinjectfinclient.cpp \
    Injectors/dcinjectmetaclient.cpp \
    Injectors/dpcinjectidxservices.cpp \
    Injectors/dpcinjectiptservices.cpp \
    Injectors/dpcinjectplaservices.cpp \
    Injectors/dscindexinjector.cpp \
    Injectors/dscinjectplaservives.cpp \
    Injectors/dscinputinjector.cpp \
    Injectors/injectdpcroutines.cpp \
    Injectors/injectdscroutines.cpp \
    Routines/dcaddinput.cpp \
    Routines/dccreatewinnerreport.cpp \
    Routines/dcgetscoresasjson.cpp \
    Routines/dcgetturnvaluesasjson.cpp \
    Routines/dcredoturn.cpp \
    Routines/dcresetservices.cpp \
    Routines/dcundoturn.cpp \
    ControllerBuilder/createdartscontroller.cpp

android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsController_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsController_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsController/ -lDartsController_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/release/ -lDartsModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/debug/ -lDartsModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
}

!android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsController
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsController
    else:unix: LIBS += -L$$OUT_PWD/../DartsController/ -lDartsController
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/release/ -lDartsModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContext/debug/ -lDartsModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
}
INCLUDEPATH += $$PWD/../DartsController
DEPENDPATH += $$PWD/../DartsController
INCLUDEPATH += $$PWD/../DartsModelsContext
DEPENDPATH += $$PWD/../DartsModelsContext
INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
