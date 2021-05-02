QT += quick testlib

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
            assembledartstournamentmodelfromjson.cpp\
            abstractjsonpersistence.cpp \
            controllerbuilder.cpp \
            dartapplication.cpp \
            dartsinputjsonassembler.cpp \
            dartsinputjsonextractor.cpp \
            dartsmultidatamodel.cpp \
            dartsscorecontroller.cpp \
            dartstournamentjsonextractor.cpp \
            iurlparser.cpp \
            jsondbcontext.cpp \
            localcricketcontroller.cpp \
            localplayermodelscontext.cpp \
            localtournamentmodelscontext.cpp \
            main.cpp \
            networkmanager.cpp \
            playerjsonassembler.cpp \
            playermodeljsonextractor.cpp \
    playermodelsservice.cpp \
            pointdartscontroller.cpp \
            pointlogisticcontroller.cpp \
            remotemodelscontext.cpp \
            scoredartscontroller.cpp \
            scoreindexcontroller.cpp \
            scorelogisticcontroller.cpp \
            sftpdatamodel.cpp \
            tournamentsjsonassembler.cpp \
            tournamentsjsonassemblerservice.cpp \
            tst_Dart2020.cpp \
            urlparser.cpp \

RESOURCES += qml.qrc

TRANSLATIONS += \
                Dart2020_da_DK.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
            assembledartsscorefromjson.h\
            playermodelsservice.h \
            scoresjsonassemblerservice.h\
            scorejsonassemblerservice.h\
            assembledartstournamentmodelfromjson.h\
            abstractdartscontroller.h \
            abstractdartsjsonassembler.h \
            dartsmultidatamodel.h \
            defaultdartsjsonassembler.h \
            ibinary.h \
            iunary.h\
            AbstractApplicationInterface.h \
            IControllerBuilder.h \
            IScoreBuilder.h \
            LinkedList.h \
            PointIndexController.h \
            ScoreValidator.h \
            abstractcontrollerbuilder.h \
            abstractcricketcontroller.h \
            abstractgamecontroller.h \
            abstractjsonpersistence.h \
            abstractmodelscontext.h \
            abstractpersistence.h \
            controllerbuilder.h \
            dartapplication.h \
            dartsinputjsonassembler.h \
            dartsinputjsonextractor.h \
            dartspointinput.h \
            dartsscorebuilder.h \
            dartsscorecontroller.h \
            dartsscoreinput.h \
            dartstournamentjsonextractor.h \
            dartstournamentmodel.h \
            ftplogisticcontrollerinterface.h \
            idartsinput.h \
            idartsinputassembler.h \
            idartsinputjsonextractor.h \
            idartspointinput.h \
            idartsscoreinput.h \
            idartstournament.h \
            idartstournamentjsonextractorservice.h \
            idartstournamentsjsonassemblerservice.h \
            idatacontext.h \
            imodel.h \
            imodelsdbcontext.h \
            indexcontrollerinterface.h \
            iplayerbuildercontext.h \
            iplayercontext.h \
            iplayerinput.h \
            iplayerjsonassemblerservice.h \
            iplayerjsonextractorservice.h \
            iplayermodel.h \
            iplayermodelbuilder.h \
            iplayermodelscontext.h \
            ipointvalidator.h \
            iresponseinterface.h \
            iscorecontroller.h \
            iscoreparameter.h \
            iscorevalidator.h \
            itournament.h \
            itournamentbuilder.h \
            itournamentmodelscontext.h \
            itournamentparameter.h \
            iurlparser.h \
            jsondbcontext.h \
            jsonextractor.h \
            localcricketcontroller.h \
            localplayermodelscontext.h \
            localtournamentmodelscontext.h \
            networkmanager.h \
            persistenceinterface.h \
            playerjsonassembler.h \
            playermodel.h \
            playermodelbuilder.h \
            playermodelbuildercontext.h \
            playermodeljsonextractor.h \
            pointScoreCalculator.h \
            pointdartscontroller.h \
            pointlogisticcontroller.h \
            pointvalidator.h \
            remotemodelscontext.h \
            replytimeout.h \
            scoreCalculatorInterface.h \
            scorebuildercontext.h \
            scorecalculator.h \
            scoredartscontroller.h \
            scoreindexcontroller.h \
            scorelogisticcontroller.h \
            sftpdatamodel.h \
            testconfiguration.h \
            tournamentbuilder.h \
            tournamentbuildercontext.h \
            tournamentcontextcollection.h \
            tournamentsjsonassemblerservice.h \
            urlparser.h \
            testeventloop.h

DISTFILES += \

#LIBS += $$PWD/SSL/libssl-1_1-x64.dll
#LIBS += $$PWD/SSL/libcrypto-1_1-x64.dll

ANDROID_ABIS = armeabi-v7a x86
