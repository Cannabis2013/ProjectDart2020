import QtQuick 2.15
import "pushbuttonScripts.js" as PBScripts
InteractiveObject {
    id: body
    clip: true
    property string text: ""
    onTextChanged: buttonText.text = qsTr(text);

    property double backgroundTransparency: 1
    onBackgroundTransparencyChanged: buttonRect.opacity = backgroundTransparency

    property int fontSize: 12
    onFontSizeChanged: buttonText.font.pointSize = fontSize

    property color hoveredColor: "#04F72D"
    property color hoveredTextColor: textColor

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: buttonRect.color = backgroundColor

    property color textColor: "black"
    onTextColorChanged: buttonText.color = textColor

    onEnabledChanged: !enabled ? opacity = 0.25 : opacity = 1

    property bool hoverEnabled: true
    onHoverEnabledChanged: body.enableHoverEvent = hoverEnabled
    // Button pressed properties
    property color pressedColor: backgroundColor
    property double pressedScale: 0.90
    // Checkable properties
    property bool isCheckable: false
    property bool checked: false
    property color checkedBackgroundColor: backgroundColor
    property color checkedTextColor: "black"
    property double checkedScale: 1

    property bool enablePressAndHold: false
    onEnablePressAndHoldChanged: body.enablePressAndHoldEvent = enablePressAndHold

    property int buttonRadius: 0
    onButtonRadiusChanged: buttonRect.radius = buttonRadius

    property url image: ""
    onImageChanged: imageDecorator.source = image

    property int imageMargins: 0
    onImageMarginsChanged: imageDecorator.anchors.margins = imageMargins

    property int imageRotation: 0
    onImageRotationChanged: imageDecorator.rotation = imageRotation

    onClickEvent: PBScripts.onClicked(text)
    onPressedEvent: PBScripts.onPressed(sustained)
    onPressAndHoldEvent: body.pressAndHoldClicked()
    onHoverEvent: PBScripts.onHover(sustained)

    signal clicked
    signal pressAndHoldClicked

    signal enableButton(bool e)
    onEnableButton: enabled = e


    signal hoveredChanged(bool status)

    onClicked: PBScripts.handleClick()

    signal clickedAndSendText(string txt)
    signal checkStateChanged(bool check)

    Rectangle
    {
        id: buttonRect
        anchors.fill: body
        radius: body.buttonRadius
        color: backgroundColor
    }
    Image{
        id: imageDecorator
        anchors.fill: parent
        anchors.margins: body.imageMargins
        rotation: body.imageRotation
    }

    Text {
        id: buttonText
        font.pointSize: fontSize
        color: body.textColor
        text: qsTr(body.text)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }
    states: [
        State {
            name: "hovered"
            PropertyChanges {
                target: buttonRect
                color : hoveredColor
                opacity: 1
            }
            PropertyChanges {
                target: buttonText
                color: hoveredTextColor
            }
            PropertyChanges {
                target: body
                checked: body.checked
            }
        },
        State {
            name: "hoveredPressed"
            PropertyChanges {
                target: buttonText
                color: hoveredTextColor
            }
            PropertyChanges{
                target: buttonRect
                color: hoveredColor
            }
            PropertyChanges {
                target: body
                checked: body.checked
            }
        },
        State {
            name: "checked"
            PropertyChanges {
                target: buttonRect
                color : checkedBackgroundColor
            }
            PropertyChanges{
                target: buttonText
                color: checkedTextColor
            }
            PropertyChanges {
                target: body
                checked : true
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: buttonRect
                scale : body.pressedScale
                color: body.pressedColor
            }
            PropertyChanges {
                target: body
                checked: body.checked
            }
        }
    ]
}
