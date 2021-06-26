import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

    GridLayout{
    id: startButtonComponentBody
    flow: GridLayout.TopToBottom
    property bool startButtonVisible: true
    onStartButtonVisibleChanged: startButton.visible = startButtonVisible
    property bool leftButtonVisible: false
    onLeftButtonVisibleChanged: leftButton.visible = leftButtonVisible
    property bool rightButtonVisible: false
    onRightButtonVisibleChanged: rightButton.visible = rightButtonVisible
    property bool pauseButtonVisible: false
    onPauseButtonVisibleChanged: pauseButton.visible = pauseButtonVisible
    property bool resumeButtonVisible: false
    onResumeButtonVisibleChanged: resumeButton.visible = resumeButtonVisible
    property bool waitButtonVisible: false
    onWaitButtonVisibleChanged: waitButton.visible = waitButtonVisible
    property bool restartButtonVisible: false
    onRestartButtonVisibleChanged: restartButton.visible = restartButtonVisible
    property bool textDescriptionVisible: true
    onTextDescriptionVisibleChanged: textDescription.visible = textDescriptionVisible
    property bool startButtonEnabled: enabled
    onStartButtonEnabledChanged: startButton.enabled = startButtonEnabled
    // Button signals
    signal startButtonClicked
    signal pressAndHoldClicked
    signal restartButtonClicked
    signal pauseButtonClicked
    signal resumeButtonClicked
    // Properties
    property bool pressAndHoldEnabled: true
    onPressAndHoldEnabledChanged: {
        startButton.enablePressAndHold = pressAndHoldEnabled;
        pauseButton.enablePressAndHold = pressAndHoldEnabled;
        resumeButton.enablePressAndHold = pressAndHoldEnabled;
    }
    // Components
    QtObject{
        id: buttonDimensions
        property int defaultHeight: 24
        property int defaultWidth: 64
    }

    MyLabel{
        id: textDescription
        Layout.alignment: Qt.AlignTop
        text: qsTr("Hold for options")
        fontColor: "white"
        fontSize: 4
        width: buttonDimensions.defaultWidth
        Layout.fillHeight: true
        wrapMode: Text.WordWrap
        verticalTextAlignment: Text.AlignBottom
        horizontalTextAlignment: Text.AlignHCenter
        visible: startButtonComponentBody.textDescriptionVisible
        onVisibleChanged: {
            visible ? textPlaceHolder.visible = false :
                                                textPlaceHolder.visible = true;
            textDescriptionAnimation.restart();
        }

        PropertyAnimation on height {
            id: textDescriptionAnimation
            from: 0
            to: restartButton.height
            duration: 125
        }
    }
    Rectangle{
        id: textPlaceHolder
        color: "transparent"
        Layout.fillHeight: true
        visible: false
    }

    PushButton{
        id: startButton
        text: "Start"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: buttonDimensions.defaultWidth
        height: buttonDimensions.defaultHeight
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: startButtonComponentBody.startButtonClicked()
        onPressAndHoldClicked: startButtonComponentBody.pressAndHoldClicked()
        enablePressAndHold: startButtonComponentBody.pressAndHoldEnabled
        visible: startButtonComponentBody.startButtonVisible
        enabled: startButtonComponent.startButtonEnabled
        onEnabledChanged: print(startButtonEnabled)
    }
    PushButton{
        id: pauseButton
        text: "Pause"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: buttonDimensions.defaultWidth
        height: buttonDimensions.defaultHeight
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: startButtonComponentBody.pauseButtonClicked()
        onPressAndHoldClicked: startButtonComponentBody.pressAndHoldClicked()
        visible: startButtonComponentBody.pauseButtonVisible
        enablePressAndHold: startButtonComponentBody.pressAndHoldEnabled
    }
    PushButton{
        id: resumeButton
        text: "Resume"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: buttonDimensions.defaultWidth
        height: buttonDimensions.defaultHeight
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: startButtonComponentBody.resumeButtonClicked()
        enablePressAndHold: startButtonComponentBody.pressAndHoldEnabled
        onPressAndHoldClicked: startButtonComponentBody.pressAndHoldClicked()
        visible: startButtonComponentBody.resumeButtonVisible
    }
    PushButton{
        id: waitButton
        text: "Wait"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: buttonDimensions.defaultWidth
        height: buttonDimensions.defaultHeight
        enablePressAndHold: false
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        enabled: false
        visible: startButtonComponentBody.waitButtonVisible
    }
    PushButton{
        id: restartButton
        text: "Restart"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navQuitButtonBackgroundColor
        hoveredColor: ThemeContext.navQuitButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: buttonDimensions.defaultWidth
        height: buttonDimensions.defaultHeight
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        visible: startButtonComponentBody.restartButtonVisible
        onClicked: restartButtonClicked()
        onVisibleChanged: restartButtonAnimation.restart()
        PropertyAnimation on height {
            id: restartButtonAnimation
            from: 0
            to: buttonDimensions.defaultHeight
            duration: 125
        }
    }
    Rectangle{
        Layout.fillHeight: true
    }
}
