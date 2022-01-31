QT -= gui
TEMPLATE = lib
DEFINES += DCFactLib

HEADERS += \
    ConverterSLAs/idcindexconverter.h \
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
    DCIndexServices/dcidxjsonbuilder.h \
    DCIndexServices/dcplayerstatsjsonbuilder.h \
    DCIndexServices/dcreqidxjsonbuilder.h \
    DCInputServices/dcassembleinput.h \
    DCInputServices/dcconvertinputs.h \
    DCInputServices/dcexternalinputservice.h \
    DCInputServices/dcinputbuilder.h \
    DCInputServices/dcinputjsonbuilder.h \
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
    DPCServices/dpccreatescore.h \
    DPCServices/dpcinputadder.h \
    DPCServices/dpcinputevaluator.h \
    DCTurnValuesServices/dccreateturnvalues.h \
    DSCServices/dsccreatescore.h \
    DSCServices/dscinputadder.h \
    DSCServices/dscinputevaluator.h \
    DartsAssemblers/assembledpc.h \
    DartsAssemblers/assembledsc.h \
    IndexServices/dpcindexcontroller.h \
    IndexServices/dscindexcontroller.h \
    InitServices/dcinitializecontroller.h \
    Injectors/dcinjectfinclient.h \
    Injectors/dcinjectmetaclient.h \
    Injectors/dcinjectroutineservices.h \
    Injectors/dpcinjectidxservices.h \
    Injectors/dpcinjectiptservices.h \
    Injectors/dpcinjectplaservices.h \
    Injectors/dpcinjectstatsservices.h \
    Injectors/dscindexinjector.h \
    Injectors/dscinjectplaservives.h \
    Injectors/dscinputinjector.h \
    Injectors/dscjsonresponseinjector.h \
    Injectors/dscstatsinjector.h \
    Injectors/injectdpcroutines.h \
    Injectors/injectdscroutines.h \
    ModelsComCtxServices/dcupdatemodelscontext.h \
    PlayerStatsServices/dcstatscontext.h \
    PlayerStatsServices/dcupdatescorerange.h \
    PlayerStatsServices/dpcupdatescorerange.h \
    ServiceRoutineServices/dcresetservices.h \
    createdartscontroller.h

SOURCES += \
    DCFinishesServices/dartscreatefinishes.cpp \
    DCFinishesServices/dcfinishbuilder.cpp \
    DCFinishesServices/defaultthresholds.cpp \
    DCInputServices/dcassembleinput.cpp \
    DCInputServices/dcconvertinputs.cpp \
    DCInputServices/dcexternalinputservice.cpp \
    DCInputServices/dcinputbuilder.cpp \
    DCJsonServices/dcjsonbuilder.cpp \
    DCMetaServices/dcmetabuilder.cpp \
    DCMetaServices/dcmetaconverter.cpp \
    DCScoresServices/dcconvertplayers.cpp \
    DCScoresServices/dcplayerbuilder.cpp \
    DCScoresServices/dpcplayerscontext.cpp \
    DCScoresServices/dscplayerscontext.cpp \
    DPCServices/dpcinputevaluator.cpp \
    DSCServices/dscinputevaluator.cpp \
    DartsAssemblers/assembledpc.cpp \
    DartsAssemblers/assembledsc.cpp \
    InitServices/dcinitializecontroller.cpp \
    Injectors/dcinjectfinclient.cpp \
    Injectors/dcinjectmetaclient.cpp \
    Injectors/dcinjectroutineservices.cpp \
    Injectors/dpcinjectidxservices.cpp \
    Injectors/dpcinjectiptservices.cpp \
    Injectors/dpcinjectplaservices.cpp \
    Injectors/dpcinjectstatsservices.cpp \
    Injectors/dscindexinjector.cpp \
    Injectors/dscinjectplaservives.cpp \
    Injectors/dscinputinjector.cpp \
    Injectors/dscjsonresponseinjector.cpp \
    Injectors/dscstatsinjector.cpp \
    Injectors/injectdpcroutines.cpp \
    Injectors/injectdscroutines.cpp \
    ModelsComCtxServices/dcupdatemodelscontext.cpp \
    PlayerStatsServices/dcupdatescorerange.cpp \
    ServiceRoutineServices/dcresetservices.cpp \
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
