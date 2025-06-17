import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0
import "playerDisplay.js" as Scripts

Rectangle {
    id: playerInfoRect
    clip: true
    color: "green"

    function update() {
        Scripts.updateValues()
    }

    QtObject {
        id: playerInfo
        property string fullName: ""
        property string formattedName: ""
    }

    Behavior on width {
        NumberAnimation {
            duration: 125
        }
    }

    Text {
        id: playerName
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        height: 36
        font.pointSize: 20
        color: "white"
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: scoreDisplayText
        anchors.bottom: statsDisplay.top
        anchors.top: playerName.bottom
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        font.pixelSize: 52
        font.weight: Font.Bold
        color: "white"
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
    }

    CompStatsDisplay {
        id: statsDisplay
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        height: 28
    }

    MouseArea {
        anchors.fill: parent
        onPressed: Scripts.openInputsDialog()
    }
}
