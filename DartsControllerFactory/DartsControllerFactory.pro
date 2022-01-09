QT -= gui
TEMPLATE = lib
DEFINES += DCFactLib

HEADERS += \
    ConverterSLAs/idcidxbuilder.h \
    ConverterServices/dcidxconverter.h \
    DCFinishesServices/dartsboundaries.h \
    DCFinishesServices/dartscreatefinishes.h \
    DCFinishesServices/dartsdefaultattempts.h \
    DCFinishesServices/dartsdivisors.h \
    DCFinishesServices/dartsfieldvalues.h \
    DCFinishesServices/dartsmodidentifiers.h \
    DCFinishesServices/dartsterminaldivisor.h \
    DCFinishesServices/dccreatefinishes.h \
    DCFinishesServices/dcfinishbuilder.h \
    DCFinishesServices/dclogisticdb.h \
    DCFinishesServices/defaultthresholds.h \
    DCIndexServices/dcidxjsonbuilder.h \
    DCIndexServices/dcplayerstatsjsonbuilder.h \
    DCIndexServices/dcreqidxjsonbuilder.h \
    DCInputServices/dcinputjsonbuilder.h \
    DCInputServices/dciptconverter.h \
    DCJsonServices/dcjsonbuilder.h \
    DCMetaServices/DCMetaInfoJsonBuilder.h \
    DCMetaServices/dcmeta.h \
    DCMetaServices/dcmetabuilder.h \
    DCMetaServices/dcmetacontext.h \
    DCMetaServices/dcsettournamentid.h \
    DCScoresServices/dcscorejsonbuilder.h \
    DCScoresServices/dcupdplastats.h \
    DCScoresServices/dpcplayerscontext.h \
    DCScoresServices/dscplayerscontext.h \
    DCServices/dcbuilderservices.h \
    DCTurnValuesServices/DCTurnValuesJsonBuilder.h \
    DCTurnValuesServices/dcturnvalues.h \
    DPCServices/DPCTurnValuesBuilder.h \
    DPCServices/dpccreatescore.h \
    DPCServices/dpcinputbuilder.h \
    DPCServices/dpcinputevaluator.h \
    DSCServices/dsccreatescore.h \
    DSCServices/dscinputbuilder.h \
    DSCServices/dscinputevaluator.h \
    DSCServices/dscvaluesbuilder.h \
    DartsAssemblers/createdpc.h \
    DartsAssemblers/createdsc.h \
    IndexServices/dpcidxctrl.h \
    IndexServices/dscindexcontroller.h \
    ModelsComCtxServices/dcaddtomodelcontext.h \
    PlayerStatsServices/dcstatscontext.h \
    PlayerStatsServices/dpcupdatescorerange.h \
    PlayerStatsServices/dscupdscorerng.h \
    createdartscontroller.h

SOURCES += \
    DCFinishesServices/dartscreatefinishes.cpp \
    DCFinishesServices/dccreatefinishes.cpp \
    DCFinishesServices/dcfinishbuilder.cpp \
    DCFinishesServices/defaultthresholds.cpp \
    DCJsonServices/dcjsonbuilder.cpp \
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
