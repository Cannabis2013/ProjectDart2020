QT += quick

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

RESOURCES += qml.qrc \

HEADERS += \
    src/DartsController/Finishes/dartsThresholds.h \
    src/DartsController/Finishes/dartsboundaries.h \
    src/DartsController/Finishes/dartscreatefinishes.h \
    src/DartsController/Finishes/dartsdivisors.h \
    src/DartsController/Finishes/dartsfieldvalues.h \
    src/DartsController/Finishes/dartsmodidentifiers.h \
    src/DartsController/Finishes/dcfinishbuilder.h \
    src/DartsController/Finishes/dclogisticdb.h \
    src/DartsController/Finishes/finishRow.h \
    src/DartsController/dartscontroller.h \
    src/DartsController/idartscontroller.h \
    src/DartsController/indexes/DartTurnIndex.h \
    src/DartsController/indexes/IDartsIndexes.h \
    src/DartsController/indexes/dartsindex.h \
    src/DartsController/indexes/dartsindexes.h \
    src/DartsController/init/dartInitInfo.h \
    src/DartsController/input/DartsInput.h \
    src/DartsController/input/DartsInternalInput.h \
    src/DartsController/input/IDartInputEvalutor.h \
    src/DartsController/input/IDartInputs.h \
    src/DartsController/input/dartinputevaluator.h \
    src/DartsController/input/dartsinputs.h \
    src/DartsController/input/inputsio.h \
    src/DartsController/players/IDartPlayers.h \
    src/DartsController/players/dartplayers.h \
    src/DartsController/responses/ErrorInfo.h \
    src/DartsController/responses/IDartsInfoResponse.h \
    src/DartsController/responses/InitialValueInfo.h \
    src/DartsController/responses/TurnInfo.h \
    src/DartsController/responses/dartsinforesponse.h \
    src/DartsController/responses/statusInfo.h \
    src/DartsController/responses/winnerInfo.h \
    src/DartsController/scores/DartsScore.h \
    src/DartsController/scores/IDartsScores.h \
    src/DartsController/scores/dartsscores.h \
    src/DartsController/scores/scoresio.h \
    src/FileIO/filejsonio.h \
    src/QmlContext/setupqmlcontext.h

SOURCES += \
    src/DartsController/Finishes/dartsThresholds.cpp \
    src/DartsController/Finishes/dartscreatefinishes.cpp \
    src/DartsController/Finishes/dcfinishbuilder.cpp \
    src/DartsController/dartscontroller.cpp \
    src/DartsController/indexes/dartsindexes.cpp \
    src/DartsController/input/dartinputevaluator.cpp \
    src/DartsController/input/dartsinputs.cpp \
    src/DartsController/input/inputsio.cpp \
    src/DartsController/players/dartplayers.cpp \
    src/DartsController/responses/dartsinforesponse.cpp \
    src/DartsController/scores/dartsscores.cpp \
    src/FileIO/filejsonio.cpp \
    src/main.cpp

