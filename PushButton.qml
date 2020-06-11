import QtQuick 2.0

Item {
    id: body

    property string text: ""
    onTextChanged: buttonText.text = text

    property int fontSize: 12
    onFontSizeChanged: buttonText = fontSize

    property color hoveredColor: "#04F72D"

    property color hoveredTextColor: textColor

    property color backgroundColor: "green"
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

    signal clicked

    MouseArea
    {
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color;
            var tColor = buttonText.color;
            if(isCheckable && checked){
                if(containsMouse)
                    buttonText.color = hoveredTextColor
                else
                    buttonText.color = body.checkedTextColor
                return;
            }
            else if(containsMouse){
                buttonRect.color = hoveredColor;
                buttonText.color = hoveredTextColor

            }
            else{

                buttonRect.color = body.backgroundColor;
                buttonText.color = body.textColor
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
            checked = isCheckable && !checked ? true : false

            if(checked){
                buttonText.color = body.checkedTextColor
                buttonRect.color = body.checkedBackgroundColor;
            }
            else if(isCheckable){
                buttonText.color = body.textColor
                buttonRect.color = body.backgroundColor;
            }

            body.clicked();
        }
    }

    clip: true

    Rectangle
    {
        id: buttonRect

        anchors.fill: body

        radius: body.buttonRadius

        color: backgroundColor

        Text {
            id: buttonText

            font.pointSize: fontSize

            color: body.textColor
            text: qsTr("Button title")

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

    }
}
