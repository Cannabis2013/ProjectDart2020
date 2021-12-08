import QtQuick 2.0

Item {
    signal startButtonClicked
    signal pressAndHoldClicked
    signal restartButtonClicked
    signal pauseButtonClicked
    signal resumeButtonClicked
    property int descriptionFontSize: 12
    property bool startButtonVisible: false
    property bool leftButtonVisible: false
    property bool rightButtonVisible: false
    property bool pauseButtonVisible: false
    property bool resumeButtonVisible: false
    property bool waitButtonVisible: false
    property bool restartButtonVisible: true
    property bool restartButtonEnabled: true
    property bool startButtonEnabled: false
    property bool pressAndHoldEnabled: true
}
