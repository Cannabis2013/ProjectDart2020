import QtQuick 2.15

Item {
    id: body

    property string text: ""
    onTextChanged: {
        var translateableText = qsTr(text);
        buttonText.text = translateableText;
    }

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

    property bool checked: false

    property bool hoverEnabled: true

    property double pressedScale: 0.90

    property bool isCheckable: false

    property color checkedBackgroundColor: "lightgreen"

    property color checkedTextColor: "black"

    property double checkedScale: 1

    property bool enablePressAndHold: false

    property int buttonRadius: 0
    onButtonRadiusChanged: buttonRect.radius = buttonRadius

    property url image: ""
    onImageChanged: imageDecorator.source = image

    property int imageMargins: 0
    onImageMarginsChanged: imageDecorator.anchors.margins = imageMargins

    property int imageRotation: 0
    onImageRotationChanged: imageDecorator.rotation = imageRotation

    signal clicked
    signal pressAndHoldClicked

    signal hoveredChanged(bool status)

    onClicked: handleClick()

    signal clickedAndSendText(string txt)
    signal checkStateChanged(bool check)

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
                state = "checked";
            }
            else
            {
                state = "";
            }
            buttonRect.scale = checked ? checkedScale : 1
            body.checkStateChanged(checked);
        }
    }

    clip: true

    MouseArea
    {
        id: buttonMouseArea
        focus: true
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            if(!body.hoverEnabled)
                return;
            else if(checked)
                return;
            if(containsMouse)
            {
                body.state = "hovered";
                body.hoveredChanged(true);
            }
            else
            {
                body.state = "";
                body.hoveredChanged(false);
            }
        }

        onPressAndHold: {
            if(body.enablePressAndHold)
            {
                pressAndHoldClicked();
            }
        }

        onPressedChanged: {
            if(containsPress)
                body.state = "pressed";
            else
                body.state = checked ? "checked" : "";
        }

        onClicked: {
            body.clicked();
            body.clickedAndSendText(text);
        }
    }

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
            }
            PropertyChanges {
                target: body
                checked: body.checked
            }
        }
    ]
}
