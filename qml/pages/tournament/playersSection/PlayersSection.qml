import QtQuick 2.0
import QtQuick.Layouts 1.3
import "playersSection.js" as Scripts

Item {
        function setPlayers(players) {
                Scripts.setPlayers(players)
        }

        function highlightPlayer(name, turnIndex) {
                Scripts.highlightRect(name, turnIndex)
        }

        PlayerInfo {
                id: playerOne
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: parent.width / 2
        }

        PlayerInfo {
                id: playerTwo
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: parent.width / 2
        }
}
