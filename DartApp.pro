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
    src/DartsController/dartsservices.h \
    src/DartsController/init/controllervalues.h \
    src/DartsController/init/iserviceinitializer.h \
    src/DartsController/init/serviceinitializer.h \
    src/DartsController/input/controllers/dartsinputcontroller.h \
    src/DartsController/input/controllers/idartsinputcontroller.h \
    src/DartsController/input/models/Input.h \
    src/DartsController/input/persistence/dartsinputs.h \
    src/DartsController/input/persistence/idartsinputs.h \
    src/DartsController/input/services/dartsinputsfilter.h \
    src/DartsController/input/services/dartsinputsupdate.h \
    src/DartsController/input/services/idartsinputsfilter.h \
    src/DartsController/input/services/idartsinputupdate.h \
    src/DartsController/players/controller/iplayerreport.h \
    src/DartsController/players/controller/playerreport.h \
    src/DartsController/players/models/dartsplayer.h \
    src/DartsController/players/persistences/dartsplayers.h \
    src/DartsController/players/persistences/idartsplayers.h \
    src/DartsController/players/services/iplayerfetcher.h \
    src/DartsController/players/services/iplayergenerator.h \
    src/DartsController/players/services/pdcchampions.h \
    src/DartsController/players/services/playerfetcher.h \
    src/DartsController/scores/controller/dartsscorescontroller.h \
    src/DartsController/scores/controller/iscorescontroller.h \
    src/DartsController/scores/dtos/DartsPlayerScores.h \
    src/DartsController/scores/dtos/dartsPlayerScore.h \
    src/DartsController/scores/models/Score.h \
    src/DartsController/scores/persistence/dartsscores.h \
    src/DartsController/scores/persistence/idartsscores.h \
    src/DartsController/scores/services/dartscalculator.h \
    src/DartsController/scores/services/dartsscoresfetch.h \
    src/DartsController/scores/services/dartsscoresupdate.h \
    src/DartsController/scores/services/idartsscoresfetch.h \
    src/DartsController/scores/services/iscorescalculator.h \
    src/DartsController/scores/services/iscoresupdate.h \
    src/DartsController/servicecollection.h \
    src/DartsController/statistics/controllers/dartsstatistics.h \
    src/DartsController/statistics/controllers/istatsreport.h \
    src/DartsController/statistics/services/dartsinputstatistics.h \
    src/DartsController/statistics/services/iinputstatistics.h \
    src/DartsController/status/dartsstatus.h \
    src/DartsController/status/idartsstatus.h \
    src/DartsController/turns/controller/dartsturncontroller.h \
    src/DartsController/turns/controller/iturncontroller.h \
    src/DartsController/turns/models/dartsindex.h \
    src/DartsController/turns/models/dartsturnindex.h \
    src/DartsController/turns/persistences/dartsindexes.h \
    src/DartsController/turns/persistences/idartsindexes.h \
    src/DartsController/turns/persistences/indexesio.h \
    src/DartsController/validation/abstractdartsevaluator.h \
    src/DartsController/validation/dartsallowances.h \
    src/DartsController/validation/dartsbeginnervalidator.h \
    src/DartsController/validation/dartsevaluators.h \
    src/DartsController/validation/dartsprofessionalevaluator.h \
    src/DartsController/validation/iplayerallowances.h \
    src/FileIO/filejsonio.h \
    src/FileIO/pagetexts.h \
    src/Setup/qmlsetup.h \
    src/Sounds/soundcontroller.h \
    src/Utils/Fonts/fontmetrics.h \
    src/Utils/Fonts/ifontmetrics.h

SOURCES += \
    src/DartsController/Finishes/dartsThresholds.cpp \
    src/DartsController/Finishes/dartscreatefinishes.cpp \
    src/DartsController/Finishes/dartsfinishes.cpp \
    src/DartsController/dartsservices.cpp \
    src/DartsController/init/controllervalues.cpp \
    src/DartsController/init/serviceinitializer.cpp \
    src/DartsController/input/controllers/dartsinputcontroller.cpp \
    src/DartsController/input/persistence/dartsinputs.cpp \
    src/DartsController/input/services/dartsinputsfilter.cpp \
    src/DartsController/input/services/dartsinputsupdate.cpp \
    src/DartsController/players/controller/playerreport.cpp \
    src/DartsController/players/models/dartsplayer.cpp \
    src/DartsController/players/persistences/dartsplayers.cpp \
    src/DartsController/players/services/pdcchampions.cpp \
    src/DartsController/players/services/playerfetcher.cpp \
    src/DartsController/scores/controller/dartsscorescontroller.cpp \
    src/DartsController/scores/persistence/dartsscores.cpp \
    src/DartsController/scores/services/dartscalculator.cpp \
    src/DartsController/scores/services/dartsscoresfetch.cpp \
    src/DartsController/scores/services/dartsscoresupdate.cpp \
    src/DartsController/statistics/controllers/dartsstatistics.cpp \
    src/DartsController/statistics/services/dartsinputstatistics.cpp \
    src/DartsController/status/dartsstatus.cpp \
    src/DartsController/turns/controller/dartsturncontroller.cpp \
    src/DartsController/turns/persistences/dartsindexes.cpp \
    src/DartsController/turns/persistences/indexesio.cpp \
    src/DartsController/validation/dartsallowances.cpp \
    src/DartsController/validation/dartsbeginnervalidator.cpp \
    src/DartsController/validation/dartsevaluators.cpp \
    src/DartsController/validation/dartsprofessionalevaluator.cpp \
    src/FileIO/filejsonio.cpp \
    src/FileIO/pagetexts.cpp \
    src/Setup/qmlsetup.cpp \
    src/Sounds/soundcontroller.cpp \
    src/Utils/Fonts/fontmetrics.cpp \
    src/main.cpp
