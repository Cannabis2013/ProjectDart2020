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

        readonly property string name: playerInfo.id


        QtObject{
                id: playerInfo
                property string id: ""
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
                anchors.leftMargin: 6
                width: parent.width - 6
                height: 24
                font.pointSize: 22
                font.weight: Font.Bold
                color: "white"
        }

        Text {
                id: playerNationality
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.bottom: parent.bottom
                height: 24
                width: 128
                font.pointSize: 12
                font.weight: Font.Bold
                verticalAlignment: Text.AlignBottom
                color: "white"
        }

        DartsCounter {
                id: dartsCounter
                anchors.right: parent.right
                anchors.rightMargin: 6
                anchors.bottom: parent.bottom
                height: 32
                width: 24
        }
}
