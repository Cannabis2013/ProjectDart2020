import QtQuick 2.0
import QtQuick.Layouts 1.3

Item
{
    id: body

    property color color: "transparent"
    onColorChanged: labelRect.color = color

    Rectangle
    {
        id: labelRect
        color: "transparent"
        anchors.fill: body
    }
    
    Text {
        id: pageLabel

        text: qsTr("Dart 2020")
        
        font.pointSize: 40
        
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.fill: body
    }
}
