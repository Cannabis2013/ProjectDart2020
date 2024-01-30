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
                width: parent.width / 2
                anchors.left: parent.left
        }

        PlayerInfo {
                id: playerTwo
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: playerOne.right
                anchors.right: parent.right
        }
}
