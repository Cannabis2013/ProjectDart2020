import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

GridLayout{
    id: body
    flow: GridLayout.TopToBottom
    signal startButtonClicked
    onStartButtonClicked: state = ""
    signal pressAndHoldClicked
    onPressAndHoldClicked: state = "optionsState"
    signal restartButtonClicked
    onRestartButtonClicked: state = ""

    signal setRestartMode
    onSetRestartMode: state = "restartState"

    signal enablePressAndHold(bool enable)
    onEnablePressAndHold: startButton.enablePressAndHold = enable

    property string startButtonText: "value"
    onStartButtonTextChanged: startButton.text = startButtonText
    property bool startButtonEnabled: false
    onStartButtonEnabledChanged: startButton.enabled = startButtonEnabled

    MyLabel{
        id: textDescription
        Layout.alignment: Qt.AlignTop
        text: qsTr("Hold for options")
        fontColor: "white"
        fontSize: 8
        width: 64
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
        text: body.startButtonText
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: 64
        height: 24
        enablePressAndHold: body.startButtonEnabled
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: body.startButtonClicked()
        onPressAndHoldClicked: body.pressAndHoldClicked()
        enabled: body.startButtonEnabled
    }
    PushButton{
        id: restartButton
        text: "Restart"
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navQuitButtonBackgroundColor
        hoveredColor: ThemeContext.navQuitButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: 64
        height: 24
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
            name: "optionsState"
            PropertyChanges {
                target: textDescription
                visible : false;
            }
            PropertyChanges {
                target: restartButton
                visible : true;
            }
            PropertyChanges {
                target: startButton
                text : "Pause"
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
                height : 24
            }
            PropertyChanges {
                target: startButton
                text : "Pause"
                visible : false
            }
        }
    ]
}
