QT += quick multimedia
CONFIG += c++20


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

HEADERS += \
    src/DartsController/Finishes/dartsThresholds.h \
    src/DartsController/Finishes/dartsboundaries.h \
    src/DartsController/Finishes/dartscreatefinishes.h \
    src/DartsController/Finishes/dartsdivisors.h \
    src/DartsController/Finishes/dartsfieldvalues.h \
    src/DartsController/Finishes/dartsfinishes.h \
    src/DartsController/Finishes/dartsmodidentifiers.h \
    src/DartsController/Finishes/dclogisticdb.h \
    src/DartsController/Finishes/finishestypes.h \
    src/DartsController/Finishes/idartsfinishes.h \
    src/DartsController/controller/IDartsController.h \
    src/DartsController/controller/controllerinitializer.h \
    src/DartsController/controller/controllerservices.h \
    src/DartsController/controller/controllervalues.h \
    src/DartsController/controller/dartscontroller.h \
    src/DartsController/controller/dartscontrollerbuilder.h \
    src/DartsController/controller/dartsturns.h \
    src/DartsController/controller/idartsturns.h \
    src/DartsController/indexes/dartsindex.h \
    src/DartsController/indexes/dartsindexes.h \
    src/DartsController/indexes/dartsturnindex.h \
    src/DartsController/indexes/idartsindexes.h \
    src/DartsController/indexes/indexesio.h \
    src/DartsController/input/IDartsInputs.h \
    src/DartsController/input/Input.h \
    src/DartsController/input/dartsinputadder.h \
    src/DartsController/input/dartsinputs.h \
    src/DartsController/input/dartsinputstrimmer.h \
    src/DartsController/input/idartsinputadder.h \
    src/DartsController/input/idartsinputtrimmer.h \
    src/DartsController/input/inputsio.h \
    src/DartsController/players/dartsplayer.h \
    src/DartsController/players/dartsplayers.h \
    src/DartsController/players/pdcchampions.h \
    src/DartsController/players/idartsplayers.h \
    src/DartsController/players/playersio.h \
    src/DartsController/responses/dartsturninfo.h \
    src/DartsController/responses/idartsturninfo.h \
    src/DartsController/scores/DartsPlayerScores.h \
    src/DartsController/scores/Score.h \
    src/DartsController/scores/dartsPlayerScore.h \
    src/DartsController/scores/dartscalculator.h \
    src/DartsController/scores/dartsinitialvalues.h \
    src/DartsController/scores/dartsscores.h \
    src/DartsController/scores/idartsscores.h \
    src/DartsController/scores/iscorescalculator.h \
    src/DartsController/scores/scoresio.h \
    src/DartsController/statistics/dartsstatistics.h \
    src/DartsController/statistics/idartsstatistics.h \
    src/DartsController/status/dartsstatus.h \
    src/DartsController/status/idartsstatus.h \
    src/DartsController/validation/abstractdartsevaluator.h \
    src/DartsController/validation/dartsallowances.h \
    src/DartsController/validation/dartsbeginnervalidator.h \
    src/DartsController/validation/dartsevaluators.h \
    src/DartsController/validation/dartsprofessionalevaluator.h \
    src/DartsController/validation/iplayerallowances.h \
    src/FileIO/filejsonio.h \
    src/FileIO/filereader.h \
    src/Setup/qmlsetup.h \
    src/Sounds/soundcontroller.h \
    src/Utils/Fonts/fontmetrics.h \
    src/Utils/Fonts/ifontmetrics.h

SOURCES += \
    src/DartsController/Finishes/dartsThresholds.cpp \
    src/DartsController/Finishes/dartscreatefinishes.cpp \
    src/DartsController/Finishes/dartsfinishes.cpp \
    src/DartsController/controller/controllerinitializer.cpp \
    src/DartsController/controller/controllerservices.cpp \
    src/DartsController/controller/controllervalues.cpp \
    src/DartsController/controller/dartscontroller.cpp \
    src/DartsController/controller/dartscontrollerbuilder.cpp \
    src/DartsController/controller/dartsturns.cpp \
    src/DartsController/indexes/dartsindexes.cpp \
    src/DartsController/indexes/indexesio.cpp \
    src/DartsController/input/dartsinputadder.cpp \
    src/DartsController/input/dartsinputs.cpp \
    src/DartsController/input/dartsinputstrimmer.cpp \
    src/DartsController/input/inputsio.cpp \
    src/DartsController/players/dartsplayers.cpp \
    src/DartsController/players/pdcchampions.cpp \
    src/DartsController/players/playersio.cpp \
    src/DartsController/responses/dartsturninfo.cpp \
    src/DartsController/scores/dartscalculator.cpp \
    src/DartsController/scores/dartsscores.cpp \
    src/DartsController/scores/scoresio.cpp \
    src/DartsController/statistics/dartsstatistics.cpp \
    src/DartsController/status/dartsstatus.cpp \
    src/DartsController/validation/dartsallowances.cpp \
    src/DartsController/validation/dartsbeginnervalidator.cpp \
    src/DartsController/validation/dartsevaluators.cpp \
    src/DartsController/validation/dartsprofessionalevaluator.cpp \
    src/FileIO/filejsonio.cpp \
    src/FileIO/filereader.cpp \
    src/Setup/qmlsetup.cpp \
    src/Sounds/soundcontroller.cpp \
    src/Utils/Fonts/fontmetrics.cpp \
    src/main.cpp
