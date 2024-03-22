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
    src/FileIO/filejsonio.h \
    src/FileIO/pagetexts.h \
    src/Finishes/dartsThresholds.h \
    src/Finishes/dartsboundaries.h \
    src/Finishes/dartscreatefinishes.h \
    src/Finishes/dartsdivisors.h \
    src/Finishes/dartsfieldvalues.h \
    src/Finishes/dartsfinishes.h \
    src/Finishes/dartsmodidentifiers.h \
    src/Finishes/dclogisticdb.h \
    src/Finishes/finishestypes.h \
    src/Finishes/idartsfinishes.h \
    src/Setup/qmlsetup.h \
    src/Sounds/soundcontroller.h \
    src/dartsservices.h \
    src/init/controllervalues.h \
    src/init/iserviceinitializer.h \
    src/init/serviceinitializer.h \
    src/input/controllers/dartsinputcontroller.h \
    src/input/controllers/idartsinputcontroller.h \
    src/input/models/input.h \
    src/input/persistence/dartsinputs.h \
    src/input/persistence/idartsinputs.h \
    src/input/services/dartsinputsfilter.h \
    src/input/services/dartsinputsupdate.h \
    src/input/services/idartsinputsfilter.h \
    src/input/services/idartsinputupdate.h \
    src/players/controller/iplayerreport.h \
    src/players/controller/playerreport.h \
    src/players/models/dartsplayer.h \
    src/players/persistences/dartsplayers.h \
    src/players/persistences/idartsplayers.h \
    src/players/services/iplayerfetcher.h \
    src/players/services/iplayergenerator.h \
    src/players/services/pdcchampions.h \
    src/players/services/playerfetcher.h \
    src/scores/controller/dartsscorescontroller.h \
    src/scores/controller/iscorescontroller.h \
    src/scores/dtos/DartsPlayerScores.h \
    src/scores/dtos/dartsPlayerScore.h \
    src/scores/models/Score.h \
    src/scores/persistence/dartsscores.h \
    src/scores/persistence/idartsscores.h \
    src/scores/services/dartscalculator.h \
    src/scores/services/dartsscoresfetch.h \
    src/scores/services/dartsscoresupdate.h \
    src/scores/services/idartsscoresfetch.h \
    src/scores/services/iscorescalculator.h \
    src/scores/services/iscoresupdate.h \
    src/servicecollection.h \
    src/statistics/controllers/dartsstatistics.h \
    src/statistics/controllers/istatsreport.h \
    src/statistics/services/istatscalculator.h \
    src/statistics/services/statscalculator.h \
    src/status/dartsstatus.h \
    src/status/idartsstatus.h \
    src/turns/controller/dartsturncontroller.h \
    src/turns/controller/iturncontroller.h \
    src/turns/models/dartsindex.h \
    src/turns/models/dartsturnindex.h \
    src/turns/persistences/dartsindexes.h \
    src/turns/persistences/idartsindexes.h \
    src/turns/persistences/indexesio.h \
    src/validation/abstractdartsevaluator.h \
    src/validation/dartsallowances.h \
    src/validation/dartsbeginnervalidator.h \
    src/validation/dartsevaluators.h \
    src/validation/dartsprofessionalevaluator.h \
    src/validation/iplayerallowances.h

SOURCES += \
    src/FileIO/filejsonio.cpp \
    src/FileIO/pagetexts.cpp \
    src/Finishes/dartsThresholds.cpp \
    src/Finishes/dartscreatefinishes.cpp \
    src/Finishes/dartsfinishes.cpp \
    src/Setup/qmlsetup.cpp \
    src/Sounds/soundcontroller.cpp \
    src/dartsservices.cpp \
    src/init/controllervalues.cpp \
    src/init/serviceinitializer.cpp \
    src/input/controllers/dartsinputcontroller.cpp \
    src/input/persistence/dartsinputs.cpp \
    src/input/services/dartsinputsfilter.cpp \
    src/input/services/dartsinputsupdate.cpp \
    src/main.cpp \
    src/players/controller/playerreport.cpp \
    src/players/models/dartsplayer.cpp \
    src/players/persistences/dartsplayers.cpp \
    src/players/services/pdcchampions.cpp \
    src/players/services/playerfetcher.cpp \
    src/scores/controller/dartsscorescontroller.cpp \
    src/scores/persistence/dartsscores.cpp \
    src/scores/services/dartscalculator.cpp \
    src/scores/services/dartsscoresfetch.cpp \
    src/scores/services/dartsscoresupdate.cpp \
    src/statistics/controllers/dartsstatistics.cpp \
    src/statistics/services/dartsAveragePoorImp.cpp \
    src/statistics/services/statscalculator.cpp \
    src/status/dartsstatus.cpp \
    src/turns/controller/dartsturncontroller.cpp \
    src/turns/persistences/dartsindexes.cpp \
    src/turns/persistences/indexesio.cpp \
    src/validation/dartsallowances.cpp \
    src/validation/dartsbeginnervalidator.cpp \
    src/validation/dartsevaluators.cpp \
    src/validation/dartsprofessionalevaluator.cpp
