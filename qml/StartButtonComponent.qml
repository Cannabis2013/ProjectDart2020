import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
StartButtonsInterface {
    id: startButtonComponentBody
    onDescriptionFontSizeChanged: textDescription.fontSize = descriptionFontSize
    onStartButtonVisibleChanged: startButton.visible = startButtonVisible
    onLeftButtonVisibleChanged: leftButton.visible = leftButtonVisible
    onRightButtonVisibleChanged: rightButton.visible = rightButtonVisible
    onPauseButtonVisibleChanged: pauseButton.visible = pauseButtonVisible
    onResumeButtonVisibleChanged: resumeButton.visible = resumeButtonVisible
    onWaitButtonVisibleChanged: waitButton.visible = waitButtonVisible
    onRestartButtonVisibleChanged: restartButton.visible = restartButtonVisible
    onStartButtonEnabledChanged: startButton.enabled = startButtonEnabled
    onPressAndHoldEnabledChanged: {
        startButton.enablePressAndHold = pressAndHoldEnabled;
        pauseButton.enablePressAndHold = pressAndHoldEnabled;
        resumeButton.enablePressAndHold = pressAndHoldEnabled;
    }
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        QtObject{
            id: buttonMetrics
            property int defaultHeight: 20
            property int defaultWidth: 64
            property int defaultFontSize: 10
        }
        PushButton{
            id: startButton
            text: "Start"
            height: buttonMetrics.defaultHeight
            width: buttonMetrics.defaultWidth
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: 6
            fontSize: buttonMetrics.defaultFontSize
            onClicked: startButtonComponentBody.startButtonClicked()
            onPressAndHoldClicked: startButtonComponentBody.pressAndHoldClicked()
            enablePressAndHold: startButtonComponentBody.pressAndHoldEnabled
            visible: startButtonComponentBody.startButtonVisible
            enabled: startButtonComponent.startButtonEnabled
        }
        PushButton{
            id: pauseButton
            text: "Pause"
            width: buttonMetrics.defaultWidth
            height: buttonMetrics.defaultHeight
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: 6
            fontSize: buttonMetrics.defaultFontSize
            onClicked: startButtonComponentBody.pauseButtonClicked()
            onPressAndHoldClicked: startButtonComponentBody.pressAndHoldClicked()
            visible: startButtonComponentBody.pauseButtonVisible
            enablePressAndHold: startButtonComponentBody.pressAndHoldEnabled
        }
        PushButton{
            id: resumeButton
            width: buttonMetrics.defaultWidth
            height: buttonMetrics.defaultHeight
            text: "Resume"
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: 6
            fontSize: buttonMetrics.defaultFontSize
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
            fontSize: buttonMetrics.defaultFontSize
            width: buttonMetrics.defaultWidth
            height: buttonMetrics.defaultHeight
            enablePressAndHold: false
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
            fontSize: buttonMetrics.defaultFontSize
            width: buttonMetrics.defaultWidth
            height: buttonMetrics.defaultHeight
            visible: startButtonComponentBody.restartButtonVisible
            onClicked: restartButtonClicked()
            onVisibleChanged: restartButtonAnimation.restart()
            PropertyAnimation on height {
                id: restartButtonAnimation
                from: 0
                to: buttonMetrics.defaultHeight
                duration: 125
            }
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }

}
