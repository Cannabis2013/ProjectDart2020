import QtQuick 2.15
import CustomItems 1.0

MyRectangle{
    id: pointTextRect
    width: 20
    height: 20
    radius: 10
    clip: true
    color: "blue"
    property string text: ""
    onTextChanged: pointText.text = text
    Text {
        id: pointText
        anchors.fill: parent
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        color: "white"
        font.pointSize: 10
    }
}
