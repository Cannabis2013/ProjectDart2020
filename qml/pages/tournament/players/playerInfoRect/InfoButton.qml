import QtQuick 6.0
import QtQuick.Controls 6.0
import "playerDisplay.js" as Scripts

Rectangle {
    id: inputButton
    width: 24
    height: 24
    color: "#5d5b59"
    signal clicked
    radius: 25
    Text {
        text: "!"
        anchors.fill: parent
        font.pointSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
    }

    MouseArea {
        anchors.fill: parent
        onPressed: inputButton.clicked()
    }
}
