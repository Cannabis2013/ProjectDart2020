QT -= gui
TEMPLATE = lib
DEFINES += DCFactLib

HEADERS += \
    ConverterServices/dcindexconverter.h \
    DCFinishesServices/dartsboundaries.h \
    DCFinishesServices/dartscreatefinishes.h \
    DCFinishesServices/dartsdefaultattempts.h \
    DCFinishesServices/dartsdivisors.h \
    DCFinishesServices/dartsfieldvalues.h \
    DCFinishesServices/dartsmodidentifiers.h \
    DCFinishesServices/dartsterminaldivisor.h \
    DCFinishesServices/dcfinishbuilder.h \
    DCFinishesServices/dclogisticdb.h \
    DCFinishesServices/defaultthresholds.h \
    Index/dcidxjsonbuilder.h \
    Index/dcreqidxjsonbuilder.h \
    DCInputServices/dcinputbuilder.h \
    DCInputServices/dcinputjsonbuilder.h \
    DCInputServices/dcjsontoinputmodels.h \
    DCJsonServices/dcjsonbuilder.h \
    DCMetaServices/DCMetaInfoJsonBuilder.h \
    DCMetaServices/dcmetabuilder.h \
    DCMetaServices/dcmetaconverter.h \
    DCMetaServices/dcmetaservice.h \
    DCMetaServices/dcsettournamentid.h \
    DCScoresServices/dcconvertplayers.h \
    DCScoresServices/dcplayerbuilder.h \
    DCScoresServices/dcscorejsonbuilder.h \
    DCScoresServices/dpcplayerscontext.h \
    DCScoresServices/dscplayerscontext.h \
    DCServices/dcbuilderservices.h \
    DCTurnValuesServices/DCTurnValuesJsonBuilder.h \
    DCTurnValuesServices/dcturnvalues.h \
    DPCServices/dpcinputadder.h \
    DPCServices/dpcinputevaluator.h \
    DCTurnValuesServices/dccreateturnvalues.h \
    DSCServices/dscinputadder.h \
    DSCServices/dscinputevaluator.h \
    DartsAssemblers/assembledpc.h \
    DartsAssemblers/assembledsc.h \
    DPCIndex/dpcindexcontroller.h \
    DSCIndex/dscindexcontroller.h \
    InitServices/dcinitialize.h \
    Injectors/dcinjectfinclient.h \
    Injectors/dcinjectmetaclient.h \
    Injectors/dcinjectroutineservices.h \
    Injectors/dpcinjectidxservices.h \
    Injectors/dpcinjectiptservices.h \
    Injectors/dpcinjectplaservices.h \
    Injectors/dscindexinjector.h \
    Injectors/dscinjectplaservives.h \
    Injectors/dscinputinjector.h \
    Injectors/dscjsonresponseinjector.h \
    Injectors/injectdpcroutines.h \
    Injectors/injectdscroutines.h \
    Routines/dcaddinputtomodelscontext.h \
    Routines/dccreatewinnerreport.h \
    Routines/dcredoturn.h \
    Routines/dcresetservices.h \
    Routines/dcundoturn.h \
    createdartscontroller.h
SOURCES += \
    DCFinishesServices/dartscreatefinishes.cpp \
    DCFinishesServices/dcfinishbuilder.cpp \
    DCFinishesServices/defaultthresholds.cpp \
    DCInputServices/dcinputbuilder.cpp \
    DCInputServices/dcjsontoinputmodels.cpp \
    DCJsonServices/dcjsonbuilder.cpp \
    DCMetaServices/dcmetabuilder.cpp \
    DCMetaServices/dcmetaconverter.cpp \
    DCScoresServices/dcconvertplayers.cpp \
    DCScoresServices/dcplayerbuilder.cpp \
    DCScoresServices/dpcplayerscontext.cpp \
    DCScoresServices/dscplayerscontext.cpp \
    DCTurnValuesServices/dccreateturnvalues.cpp \
    DPCServices/dpcinputevaluator.cpp \
    DSCServices/dscinputevaluator.cpp \
    DartsAssemblers/assembledpc.cpp \
    DartsAssemblers/assembledsc.cpp \
    DPCIndex/dpcindexcontroller.cpp \
    InitServices/dcinitialize.cpp \
    Injectors/dcinjectfinclient.cpp \
    Injectors/dcinjectmetaclient.cpp \
    Injectors/dcinjectroutineservices.cpp \
    Injectors/dpcinjectidxservices.cpp \
    Injectors/dpcinjectiptservices.cpp \
    Injectors/dpcinjectplaservices.cpp \
    Injectors/dscindexinjector.cpp \
    Injectors/dscinjectplaservives.cpp \
    Injectors/dscinputinjector.cpp \
    Injectors/dscjsonresponseinjector.cpp \
    Injectors/injectdpcroutines.cpp \
    Injectors/injectdscroutines.cpp \
    Routines/dcaddinputtomodelscontext.cpp \
    Routines/dccreatewinnerreport.cpp \
    Routines/dcredoturn.cpp \
    Routines/dcresetservices.cpp \
    Routines/dcundoturn.cpp \
    createdartscontroller.cpp

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
