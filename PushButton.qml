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
    onCheckedChanged: isCheckable ||checked == false ? checked = checked : checked = false

    property bool isCheckable: false

    signal clicked

    MouseArea
    {
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color;
            var tColor = buttonText.color;

            if(!Qt.colorEqual(c,hoveredColor) || !Qt.colorEqual(tColor,hoveredTextColor)){
                buttonText.color = hoveredTextColor
                buttonRect.color = hoveredColor;
            }
            else
            {
                buttonText.color = textColor
                buttonRect.color = body.backgroundColor;
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

        onClicked: body.clicked()
    }

    clip: true

    Rectangle
    {
        id: buttonRect

        anchors.fill: body

        radius: 20

        color: "green"

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
