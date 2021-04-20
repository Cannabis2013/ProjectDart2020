import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

GridLayout{
    id: body
    flow: GridLayout.TopToBottom
    // Button signals
    signal startButtonClicked
    signal pressAndHoldClicked
    onPressAndHoldClicked: state = "optionsState"
    signal restartButtonClicked
    onRestartButtonClicked: state = "startState"
    signal pauseButtonClicked
    signal resumeButtonClicked
    // States
    signal setStartMode
    onSetStartMode: state = "startState"
    signal setRunningMode
    onSetRunningMode: state = "runningState"
    signal setRestartMode
    onSetRestartMode: state = "restartState"
    signal setWaitState
    onSetWaitState: state = "waitState"
    signal setStoppedState
    onSetStoppedState: state = "stoppedState"
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
        fontSize: 8
        width: buttonDimensions.defaultWidth
        Layout.fillHeight: true
        wrapMode: Text.WordWrap
        verticalTextAlignment: Text.AlignBottom
        horizontalTextAlignment: Text.AlignHCenter
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
        onClicked: body.startButtonClicked()
        onPressAndHoldClicked: body.pressAndHoldClicked()
        enablePressAndHold: body.pressAndHoldEnabled
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
        onClicked: body.pauseButtonClicked()
        onPressAndHoldClicked: body.pressAndHoldClicked()
        visible: false
        enablePressAndHold: body.pressAndHoldEnabled
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
        onClicked: body.resumeButtonClicked()
        enablePressAndHold: body.startButtonEnabled
        onPressAndHoldClicked: body.pressAndHoldClicked()
        visible: false
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
        visible: false
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
        visible: false
        onClicked: restartButtonClicked()
        onVisibleChanged: restartButtonAnimation.restart()
        PropertyAnimation on height {
            id: restartButtonAnimation
            from: 0
            to: restartButton.height
            duration: 125
        }
    }

    Rectangle{
        Layout.fillHeight: true
    }

    states: [
        State {
            name: "startState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: startButton
                visible: true
            }
            PropertyChanges {
                target: pauseButton
                visible: false
            }
            PropertyChanges {
                target: resumeButton
                visible: false
            }
            PropertyChanges {
                target: waitButton
                visible: false
            }
        },
        State {
            name: "runningState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: startButton
                visible: false
            }
            PropertyChanges {
                target: pauseButton
                visible: true
            }
            PropertyChanges {
                target: resumeButton
                visible: false
            }
            PropertyChanges {
                target: waitButton
                visible: false
            }
            PropertyChanges {
                target: restartButton
                visible: false
            }

        },
        State {
            name: "waitState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: startButton
                visible: false
            }
            PropertyChanges {
                target: pauseButton
                visible: false
            }
            PropertyChanges {
                target: resumeButton
                visible: false
            }
            PropertyChanges {
                target: waitButton
                visible: true
            }
            PropertyChanges {
                target: restartButton
                visible: false
            }
        },
        State {
            name: "stoppedState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: startButton
                visible: false
            }
            PropertyChanges {
                target: pauseButton
                visible: false
            }
            PropertyChanges {
                target: resumeButton
                visible: true
            }
            PropertyChanges {
                target: waitButton
                visible: false
            }
            PropertyChanges {
                target: restartButton
                visible: false
            }
        },
        State {
            name: "optionsState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: startButton
                visible: visible
            }
            PropertyChanges {
                target: pauseButton
                visible: visible
            }
            PropertyChanges {
                target: resumeButton
                visible: visible
            }
            PropertyChanges {
                target: waitButton
                visible: visible
            }
            PropertyChanges {
                target: restartButton
                visible: true
            }
        },
        State {
            name: "restartState"
            PropertyChanges {
                target: textDescription
                visible : false
            }
            PropertyChanges {
                target: restartButton
                visible : true
                height : restartButton.height
            }
        }
    ]
}
