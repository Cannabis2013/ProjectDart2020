import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compPlayerInfo.js" as Scripts

Item {
        id: infoRect

        height: 96

        readonly property string name: playerInfo.id

        QtObject {
                id: playerInfo
                property string id: ""
        }

        function setPlayer(player) {
                Scripts.setPlayer(player)
        }

        function hideDarts(count) {
                dartsCounter.hideDarts(count)
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
                height: 48
                width: 36
                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.bottom: parent.bottom
        }
}
