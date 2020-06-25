import QtQuick 2.0

Item {
    id: buttonBody

    property color defaultBackDropHoverColor: "white"

    property int orientation: 0x2

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true

        onHoveredChanged: {
            if(containsMouse)
                backDropRect.color = defaultBackDropHoverColor
            else
                backDropRect.color = "transparent"
        }

        onPressedChanged: {
            var s = backDropRect.scale;
            var alteredS = 0.90
            if(s !== alteredS)
            {
                backDropRect.scale = alteredS
            }
            else
            {
                backDropRect.scale = 1
            }
        }
    }

    Rectangle{
        id: backDropRect

        color: "transparent"

        anchors.fill: parent

        radius: 45

        Image {
            id: imageDecorator
            source: "qrc:/pictures/Ressources/arrow.png"

            anchors.fill: parent

            anchors.margins: 10

            rotation: orientation == 0x1 ? 0 : 180
        }
    }
}
