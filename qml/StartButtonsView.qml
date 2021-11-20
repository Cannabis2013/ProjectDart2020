import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "jsPopUpBuilder.js" as PopupBuilder
StartButtonsInterface {
    id: startButtons
    onDescriptionFontSizeChanged: textDescription.fontSize = descriptionFontSize
    onStartButtonVisibleChanged: startButton.visible = startButtonVisible
    onLeftButtonVisibleChanged: leftButton.visible = leftButtonVisible
    onRightButtonVisibleChanged: rightButton.visible = rightButtonVisible
    onPauseButtonVisibleChanged: pauseButton.visible = pauseButtonVisible
    onResumeButtonVisibleChanged: resumeButton.visible = resumeButtonVisible
    onWaitButtonVisibleChanged: waitButton.visible = waitButtonVisible
    onRestartButtonVisibleChanged: restartButton.visible = restartButtonVisible
    onRestartButtonEnabledChanged: restartButton.enabled = restartButtonEnabled
    onStartButtonEnabledChanged: startButton.enabled = startButtonEnabled
    onPressAndHoldEnabledChanged: {
        startButton.enablePressAndHold = pressAndHoldEnabled;
        pauseButton.enablePressAndHold = pressAndHoldEnabled;
        resumeButton.enablePressAndHold = pressAndHoldEnabled;
    }
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        rowSpacing: 0
        columnSpacing: 0
        QtObject{
            id: defaultButtonGeometries
            property double defaultHeight: 24
            property int defaultWidth: 64
            property int defaultFontSize: 12
            property int defaultRadius: 0
        }
        PushButton{
            id: startButton
            text: "Start"
            pressedScale: 1
            height: defaultButtonGeometries.defaultHeight
            width: defaultButtonGeometries.defaultWidth
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: defaultButtonGeometries.defaultRadius
            fontSize: defaultButtonGeometries.defaultFontSize
            onClicked: startButtons.startButtonClicked()
            visible: startButtons.startButtonVisible
            enabled: startButtonComponent.startButtonEnabled
        }
        PushButton{
            id: pauseButton
            text: "Pause"
            pressedScale: 1
            width: defaultButtonGeometries.defaultWidth
            height: defaultButtonGeometries.defaultHeight
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: defaultButtonGeometries.defaultRadius
            fontSize: defaultButtonGeometries.defaultFontSize
            onClicked: startButtons.pauseButtonClicked()
            visible: startButtons.pauseButtonVisible
            enablePressAndHold: startButtons.pressAndHoldEnabled
        }
        PushButton{
            id: resumeButton
            text: "Resume"
            pressedScale: 1
            width: defaultButtonGeometries.defaultWidth
            height: defaultButtonGeometries.defaultHeight
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: defaultButtonGeometries.defaultRadius
            fontSize: defaultButtonGeometries.defaultFontSize
            onClicked: startButtons.resumeButtonClicked()
            visible: startButtons.resumeButtonVisible
        }
        PushButton{
            id: waitButton
            text: "Wait"
            pressedScale: 1
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navStartButtonBackgroundColor
            hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
            buttonRadius: defaultButtonGeometries.defaultRadius
            fontSize: defaultButtonGeometries.defaultFontSize
            width: defaultButtonGeometries.defaultWidth
            height: defaultButtonGeometries.defaultHeight
            enabled: false
            visible: startButtons.waitButtonVisible
        }
        PushButton{
            id: restartButton
            text: "Restart"
            pressedScale: 1
            textColor: ThemeContext.navStartButtonTextColor
            backgroundColor: ThemeContext.navQuitButtonBackgroundColor
            hoveredColor: ThemeContext.navRestartButtHovColor
            buttonRadius: defaultButtonGeometries.defaultRadius
            fontSize: defaultButtonGeometries.defaultFontSize
            width: defaultButtonGeometries.defaultWidth
            height: defaultButtonGeometries.defaultHeight
            onClicked: PopupBuilder.createConfirmPopUp(applicationWindow,undefined,restartButtonClicked);
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
}
