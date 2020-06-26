import QtQuick 2.0

Item {
    id: pushButtonbody

    property string text: ""
    onTextChanged: buttonText.text = text

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
    onCheckedChanged: isCheckable || checked == false ? checked = checked : checked = false

    property bool isCheckable: false

    property color checkedBackgroundColor: "lightgreen"

    property color checkedTextColor: "black"

    property int buttonRadius: 20
    onButtonRadiusChanged: buttonRect.radius = buttonRadius

    property url image: ""
    onImageChanged: imageDecorator.source = image

    property int imageMargins: 0
    onImageMarginsChanged: imageDecorator.anchors.margins = imageMargins

    property int imageRotation: 0
    onImageRotationChanged: imageDecorator.rotation = imageRotation

    signal clicked
    signal clickedText(string txt)
    signal checkStateChanged(bool check)

    MouseArea
    {
        id: buttonMouseArea
        anchors.fill: pushButtonbody
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color;
            var tColor = buttonText.color;
            if(isCheckable && checked){
                if(containsMouse)
                    buttonText.color = hoveredTextColor
                else
                    buttonText.color = pushButtonbody.checkedTextColor
                return;
            }
            else if(containsMouse){
                buttonRect.color = hoveredColor;
                buttonText.color = hoveredTextColor

            }
            else{

                buttonRect.color = pushButtonbody.backgroundColor;
                buttonText.color = pushButtonbody.textColor
            }
        }

        onPressedChanged: {
            var s = buttonRect.scale;
            var alteredS = 0.90
            if(s !== alteredS)
            {
                buttonRect.scale = alteredS
            }
            else
            {
                buttonRect.scale = 1
            }
        }

        onClicked: {
            if(isCheckable)
            {
                checked = !checked ? true : false;
                pushButtonbody.checkStateChanged(checked);

            }


            if(checked){
                buttonText.color = pushButtonbody.checkedTextColor
                buttonRect.color = pushButtonbody.checkedBackgroundColor;
            }
            else if(isCheckable){
                buttonText.color = pushButtonbody.textColor
                buttonRect.color = pushButtonbody.backgroundColor;
            }

            pushButtonbody.clicked();
            pushButtonbody.clickedText(text);
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

    }
}
