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

    property color textColor: "white"
    onTextColorChanged: buttonText.color = textColor

    onEnabledChanged: !enabled ? opacity = 0.25 : opacity = 1

    property bool checked: false
    onCheckedChanged: isCheckable || checked == false ? checked = checked : checked = false

    property bool isCheckable: false

    property color checkedColor: "lightgreen"

    signal clicked

    MouseArea
    {
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color;
            var tColor = buttonText.color;
            if(checked || isCheckable){
                if(!Qt.colorEqual(tColor,hoveredTextColor))
                    buttonText.color = hoveredTextColor
                else
                    buttonText.color = body.textColor
            }

            else if(!Qt.colorEqual(c,hoveredColor))
                buttonRect.color = hoveredColor;
            else
                buttonRect.color = body.backgroundColor;
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

            if(checked)
                buttonRect.color = body.checkedColor;
            else if(isCheckable)
                buttonRect.color = body.backgroundColor;

            body.clicked();
        }
    }

    clip: true

    Rectangle
    {
        id: buttonRect

        anchors.fill: body

        radius: 20

        color: backgroundColor

        Text {
            id: buttonText

            font.pointSize: fontSize

            color: "white"
            text: qsTr("Button title")

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

    }
}
