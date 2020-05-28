import QtQuick 2.0

Item {
    id: body

    width: 128
    height: 50

    property string text: ""
    onTextChanged: buttonText.text = text

    property color backgroundColor: "green"
    onBackgroundColorChanged: buttonRect.color = backgroundColor

    property color textColor: "white"
    onTextColorChanged: buttonText.color = textColor

    onEnabledChanged: !enabled ? opacity = 0.25 : opacity = 1

    signal clicked

    MouseArea
    {
        anchors.fill: body
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color;

            if(!Qt.colorEqual(c,"#04F72D"))
                buttonRect.color = "#04F72D";
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

            font.pointSize: 12

            color: "white"
            text: qsTr("Button title")

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

    }
}
