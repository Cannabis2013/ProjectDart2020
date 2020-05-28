import QtQuick 2.0

Item {
    id: buttonContainer

    property string text: ""
    onTextChanged: buttonText.text = text

    property string backgroundColor: "green"
    onBackgroundColorChanged: buttonRect.color = backgroundColor

    property string textColor: "white"
    onTextColorChanged: buttonText.color = textColor

    signal clicked

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            var c = buttonRect.color.toString();
            if(c !== "#d3d3d3")
                buttonRect.color = "#d3d3d3";
            else
                buttonRect.color = buttonContainer.backgroundColor;
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

        onClicked: buttonContainer.clicked()
    }

    width: 50
    height: 40

    clip: true

    Rectangle
    {
        id: buttonRect

        anchors.fill: parent

        radius: 20

        color: "green"

        Text {
            id: buttonText

            font.pointSize: 12

            color: "white"
            text: qsTr("Button title")

            anchors.centerIn: parent
        }

    }
}
