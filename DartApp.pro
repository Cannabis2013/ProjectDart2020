QT += quick quickcontrols2
CONFIG += c++23

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
    src/FileIO/filehtml.h \
    src/FileIO/filejsonio.h \
    src/Finishes/dartsfinishes.h \
    src/Finishes/finishconstructor.h \
    src/dartsservices.h \
    src/init/controllervalues.h \
    src/init/dartsinitializer.h \
    src/init/iserviceinitializer.h \
    src/input/dartsinput.h \
    src/input/dartsinputcontroller.h \
    src/input/dartsinputs.h \
    src/input/dartsinputsfilter.h \
    src/input/dartsinputsupdater.h \
    src/input/idartsinputcontroller.h \
    src/input/idartsinputs.h \
    src/input/idartsinputsfilter.h \
    src/input/idartsinputsupdater.h \
    src/input/inputCandidate.h \
    src/players/IPlayers.h \
    src/players/dartsplayers.h \
    src/players/idartsplayers.h \
    src/players/playercontroller.h \
    src/scores/dartsreminings.h \
    src/scores/idartsremainings.h \
    src/scores/iremainings.h \
    src/scores/remainingscontroller.h \
    src/servicecollection.h \
    src/statistics/dartsstatistics.h \
    src/statistics/istatscalculator.h \
    src/statistics/istatsreport.h \
    src/statistics/statscalculator.h \
    src/turns/dartsindex.h \
    src/turns/dartsindexes.h \
    src/turns/dartsturncontroller.h \
    src/turns/dartsturnindex.h \
    src/turns/idartsindexes.h \
    src/turns/indexesio.h \
    src/turns/iturncontroller.h \
    src/validation/dartscloseningfilter.h \
    src/validation/iclosurefilter.h \
    src/validation/iopenvalidator.h \
    src/validation/jsonopenpersistence.h \
    src/validation/openvalidator.h \
    src/winner/iwinnercontroller.h \
    src/winner/winnerinfo.h

SOURCES += \
    src/FileIO/filehtml.cpp \
    src/FileIO/filejsonio.cpp \
    src/Finishes/dartsfinishes.cpp \
    src/Finishes/finishConstructor.cpp \
    src/dartsservices.cpp \
    src/init/dartsinitializer.cpp \
    src/input/dartsinput.cpp \
    src/input/dartsinputcontroller.cpp \
    src/input/dartsinputs.cpp \
    src/input/dartsinputsfilter.cpp \
    src/input/dartsinputsupdater.cpp \
    src/main.cpp \
    src/players/dartsplayers.cpp \
    src/players/playercontroller.cpp \
    src/scores/dartsreminings.cpp \
    src/scores/remainingscontroller.cpp \
    src/statistics/dartsaverage_imp_1.cpp \
    src/statistics/dartsstatistics.cpp \
    src/statistics/statscalculator.cpp \
    src/turns/dartsindexes.cpp \
    src/turns/dartsturncontroller.cpp \
    src/turns/indexesio.cpp \
    src/validation/dartscloseningfilter.cpp \
    src/validation/jsonopenpersistence.cpp \
    src/validation/openvalidator.cpp \
    src/winner/winnerinfo.cpp

DISTFILES += \
    qml/components/ConfirmDialog.qml \
    qml/components/ImageCarousel.qml \
    qml/components/InfoDisplay.qml \
    qml/components/InputControls.qml \
    qml/components/KeyPad.qml \
    qml/components/MessagesDisplay.qml \
    qml/components/NumberKeyPad.qml \
    qml/components/Pad.qml \
    qml/components/PageHeader.qml \
    qml/components/PlayersInfoScreen.qml \
    qml/components/PushButton.qml \
    qml/components/TurnControls.qml \
    qml/components/ValueSelector.qml \
    qml/components/WinnerScreen.qml \
    qml/main.qml \
    qml/pages/About.qml \
    qml/pages/Calculator.qml \
    qml/pages/Game.qml \
    qml/pages/Setup.qml \
    qml/pages/Start.qml \
    qml/scripts/Game.js \
    qml/scripts/nameUtils.js \
    qml/scripts/setupPage.js \
    qml/scripts/startPage.js
