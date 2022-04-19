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

RESOURCES += qml.qrc

SOURCES += \
        DartsTableContext/dartstabledatacontext.cpp \
        DartsTableContext/dartstablemodel.cpp \
        DartsTableContext/dartstableslas.cpp \
        QmlContext/qmlpropertiesbuilder.cpp \
        main.cpp

HEADERS += \
    DartsTableContext/DataContextSLAs/idartstabledatacontext.h \
    DartsTableContext/FontMetrics/greatestheight.h \
    DartsTableContext/FontMetrics/greatestwidth.h \
    DartsTableContext/FontMetrics/mhtablesectionmetrics.h \
    DartsTableContext/LinkedList/linkedlist.h \
    DartsTableContext/QMLDartsDataModel/dartsplayerdatamodel.h \
    DartsTableContext/QMLTableMetrics/mhtablecolumnwidth.h \
    DartsTableContext/QMLTableMetrics/mhtablerowheight.h \
    DartsTableContext/TableCellsServices/dartsinitrowvalues.h \
    DartsTableContext/TableSectionsSLAs/itablecellcontext.h \
    DartsTableContext/TableSectionsSLAs/itableinitrowvalues.h \
    DartsTableContext/TableSectionsSLAs/itablesectioncontext.h \
    DartsTableContext/TableSectionsSLAs/itablesectionmanipulator.h \
    DartsTableContext/createqmlvariants.h \
    DartsTableContext/dartsdatacontextitemutility.h \
    DartsTableContext/dartstablecellcontext.h \
    DartsTableContext/dartstablecreatecolumnindices.h \
    DartsTableContext/dartstablecreatecolumns.h \
    DartsTableContext/dartstablecreaterowindices.h \
    DartsTableContext/dartstabledatacontext.h \
    DartsTableContext/dartstabledimensions.h \
    DartsTableContext/dartstablemodel.h \
    DartsTableContext/dartstablesectionmanipulator.h \
    DartsTableContext/dartstablesectionutility.h \
    DartsTableContext/dartstableslas.h \
    DartsTableContext/dptablemodel.h \
    DartsTableContext/dstablemodel.h \
    DartsTableContext/idartstablesectionutility.h \
    DartsTableContext/igetdatafromdatacontext.h \
    DartsTableContext/iqmldatabuilder.h \
    DartsTableContext/itableindicevalues.h \
    QmlContext/qmlpropertiesbuilder.h \
    SetupQmlApp/registerqmldartstabletypes.h \
    SetupQmlApp/registerqmlsingletons.h \
    SetupQmlApp/registerqmltableutils.h \
    SetupQmlApp/registerqmltypes.h \
    SetupQmlApp/setupqmlcontext.h

DISTFILES += \
    Ressources/arrow.png \
    Ressources/checkmark.png \
    Ressources/dartpic.jpg \
    Ressources/dartpic.png \
    Ressources/darttournamentmod.png \
    Ressources/fck.png \
    Ressources/fck_jersey_logo.png \
    Ressources/hitler.png \
    Ressources/pngfuel.com.png \
    Ressources/s12_1.jpg \
    Ressources/skull.png \
    Ressources/tuborgclassic.png \
    Ressources/users.png

!android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsModelsContext
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsModelsContext
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsController/release/ -lDartsController
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsController/debug/ -lDartsController
    else:unix: LIBS += -L$$OUT_PWD/../DartsController/ -lDartsController
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsControllerFactory/release/ -lDartsControllerFactory
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsControllerFactory/debug/ -lDartsControllerFactory
    else:unix: LIBS += -L$$OUT_PWD/../DartsControllerFactory/ -lDartsControllerFactory
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/release/ -lDartsModelsContextFactory
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/debug/ -lDartsModelsContextFactory
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/ -lDartsModelsContextFactory
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayersContextFactory/release/ -lPlayersContextFactory
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayersContextFactory/debug/ -lPlayersContextFactory
    else:unix: LIBS += -L$$OUT_PWD/../PlayersContextFactory/ -lPlayersContextFactory
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/release/ -lDartsStatistics
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/debug/ -lDartsStatistics
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatistics/ -lDartsStatistics
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/release/ -lDartsStatisticsFactory
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/debug/ -lDartsStatisticsFactory
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/ -lDartsStatisticsFactory
}

android {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/release/ -lPlayerModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayerModelsContext/debug/ -lPlayerModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayerModelsContext/ -lPlayerModelsContext_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -lDartsModelsContext_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -lDartsModelsContext_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContext/ -lDartsModelsContext_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsController/release/ -lDartsController_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsController/debug/ -lDartsController_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsController/ -lDartsController_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsControllerFactory/release/ -lDartsControllerFactory_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsControllerFactory/debug/ -lDartsControllerFactory_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsControllerFactory/ -lDartsControllerFactory_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/release/ -lDartsModelsContextFactory_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/debug/ -lDartsModelsContextFactory_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsModelsContextFactory/ -lDartsModelsContextFactory_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PlayersContextFactory/release/ -lPlayersContextFactory_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PlayersContextFactory/debug/ -lPlayersContextFactory_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../PlayersContextFactory/ -lPlayersContextFactory_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/release/ -lDartsStatistics_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatistics/debug/ -lDartsStatistics_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatistics/ -lDartsStatistics_arm64-v8a
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/release/ -lDartsStatisticsFactory_arm64-v8a
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/debug/ -lDartsStatisticsFactory_arm64-v8a
    else:unix: LIBS += -L$$OUT_PWD/../DartsStatisticsFactory/ -lDartsStatisticsFactory_arm64-v8a
}

INCLUDEPATH += $$PWD/../PlayerModelsContext
DEPENDPATH += $$PWD/../PlayerModelsContext
INCLUDEPATH += $$PWD/../DartsModelsContext
DEPENDPATH += $$PWD/../DartsModelsContext
INCLUDEPATH += $$PWD/../DartsController
DEPENDPATH += $$PWD/../DartsController
INCLUDEPATH += $$PWD/../DartsControllerFactory
DEPENDPATH += $$PWD/../DartsControllerFactory
INCLUDEPATH += $$PWD/../DartsModelsContextFactory
DEPENDPATH += $$PWD/../DartsModelsContextFactory
INCLUDEPATH += $$PWD/../PlayersContextFactory
DEPENDPATH += $$PWD/../PlayersContextFactory
INCLUDEPATH += $$PWD/../DartsStatistics
DEPENDPATH += $$PWD/../DartsStatistics
INCLUDEPATH += $$PWD/../DartsStatisticsFactory

ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsModelsContext/libDartsModelsContext_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsModelsContextFactory/libDartsModelsContextFactory_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsController/libDartsController_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsControllerFactory/libDartsControllerFactory_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsStatistics/libDartsStatistics_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../DartsStatisticsFactory/libDartsStatisticsFactory_arm64-v8a.so
ANDROID_EXTRA_LIBS += $$OUT_PWD/../PlayerModelsContext/libPlayerModelsContext_arm64-v8a.so
