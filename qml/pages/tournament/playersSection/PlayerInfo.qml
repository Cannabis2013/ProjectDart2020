import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerInfo.js" as Scripts

Rectangle {
        id: infoRect

        color: "green"

        Behavior on color {
                ColorAnimation {
                        duration: 300
                }
        }

        NumberAnimation on width {
                id: widthAni
                duration: 500
                running: false
                onFinished: Scripts.restoreZValue()
        }

        readonly property string name: playerInfo.id

        QtObject {
                id: playerInfo
                property string id: ""
                property bool enlarged: false
                property int initialZValue: -1
        }

        function setPlayer(name, nationality) {
                Scripts.setPlayer(name, nationality)
        }

        function highlight(status, count) {
                Scripts.highlight(status, count)
        }

        Text {
                id: playerName
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 6
                anchors.rightMargin: 6
                height: 48
                font.pointSize: 36
                font.weight: Font.Bold
                color: "white"
        }

        Text {
                id: playerNationality
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.bottom: parent.bottom
                height: 40
                width: 64
                font.pointSize: 32
                verticalAlignment: Text.AlignBottom
                color: "white"
        }

        DartsCounter {
                id: dartsCounter
                height: 76
                width: 57
                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.bottom: parent.bottom
        }

        MouseArea {
                anchors.fill: parent
                onClicked: Scripts.handleSizeChangeRequest()
        }

        Component.onCompleted: Scripts.init()
}
