import QtQuick 2.0

/*
  Orientation = {LeftOriented = 0x01, rightOriented = 0x02}
  */

Item {
    id: buttonBody

    signal clicked

    property color defaultBackDropHoverColor: "white"

    property url source: ""
    onSourceChanged: imageDecorator.source = source

    property int orientation: 0x02

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

        onPressed: clicked()
    }

    Rectangle{
        id: backDropRect

        color: "transparent"

        anchors.fill: parent

        radius: 45

        Image {
            id: imageDecorator
            source: buttonBody.source

            anchors.fill: parent

            anchors.margins: 10

            rotation: orientation == 0x02 ? 0 : 180
        }
    }
}
