import QtQuick 2.0

Item {
    id: pushButtonbody

    property string text: ""
    onTextChanged: {
        var translateableText = qsTr(text);
        buttonText.text = translateableText;
    }

    property int fontSize: 12
    onFontSizeChanged: buttonText = fontSize

    property color hoveredColor: "#04F72D"
    property color hoveredTextColor: textColor

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: buttonRect.color = backgroundColor

    property color textColor: "black"
    onTextColorChanged: buttonText.color = textColor

    onEnabledChanged: !enabled ? opacity = 0.25 : opacity = 1

    property bool checked: false

    property bool hoverEnabled: true

    property double pressedScale: 0.90

    property bool isCheckable: false

    property color checkedBackgroundColor: "lightgreen"

    property color checkedTextColor: "black"

    property double checkedScale: 1

    property int buttonRadius: 20
    onButtonRadiusChanged: buttonRect.radius = buttonRadius

    property url image: ""
    onImageChanged: imageDecorator.source = image

    property int imageMargins: 0
    onImageMarginsChanged: imageDecorator.anchors.margins = imageMargins

    property int imageRotation: 0
    onImageRotationChanged: imageDecorator.rotation = imageRotation

    signal clicked
    onClicked: handleClick()

    signal emitBodyText(string txt)
    signal emitCheckState(bool check)

    property Rectangle buttonBody: buttonRect

    function setEnabled(enable)
    {
        enabled = enable;
    }

    function handleClick()
    {
        if(isCheckable)
        {
            if(!checked){
                buttonRect.state = "checked";
            }
            else
            {
                buttonRect.state = "";
            }
            buttonRect.scale = checked ? checkedScale : 1
            pushButtonbody.emitCheckState(checked);
        }
    }

    MouseArea
    {
        id: buttonMouseArea
        anchors.fill: pushButtonbody
        hoverEnabled: true
        onHoveredChanged: {
            if(!pushButtonbody.hoverEnabled)
                return;
            var c = buttonRect.color;
            var tColor = buttonText.color;
            if(isCheckable && checked){
                if(containsMouse)
                    buttonRect.state = "hoveredPressed"
                else
                    buttonRect.state = "checked";
                return;
            }
            else if(containsMouse){
                buttonRect.state = "hovered";

            }
            else{
                buttonRect.state = "";
            }
        }

        onPressedChanged: {
            var s = buttonRect.scale;
            var alteredS = pressedScale
            if(s !== alteredS)
                buttonRect.state = "pressed";
            else
                buttonRect.state = checked ? "checked" : "";
        }

        onClicked: {
            pushButtonbody.clicked();
            pushButtonbody.emitBodyText(text);
        }
    }

    clip: true

    Rectangle
    {
        id: buttonRect

        anchors.fill: pushButtonbody

        radius: pushButtonbody.buttonRadius

        color: backgroundColor
        Image{
            id: imageDecorator

            anchors.fill: parent
            anchors.margins: pushButtonbody.imageMargins

            rotation: pushButtonbody.imageRotation
        }

        Text {
            id: buttonText

            font.pointSize: fontSize

            color: pushButtonbody.textColor
            text: qsTr(pushButtonbody.text)

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
                }
                PropertyChanges {
                    target: buttonText
                    color: hoveredTextColor
                }
                PropertyChanges {
                    target: pushButtonbody
                    checked: pushButtonbody.checked
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
                    target: pushButtonbody
                    checked: pushButtonbody.checked
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
                    target: pushButtonbody
                    checked : true
                }
            },
            State {
                name: "pressed"
                PropertyChanges {
                    target: buttonRect
                    scale : pushButtonbody.pressedScale
                }
                PropertyChanges {
                    target: pushButtonbody
                    checked: pushButtonbody.checked
                }
            }
        ]
    }
}
