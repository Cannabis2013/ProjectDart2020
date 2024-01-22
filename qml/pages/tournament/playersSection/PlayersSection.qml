import QtQuick 2.0
import QtQuick.Layouts 1.3
import "playersSection.js" as Scripts

Rectangle {
        color: "green"

        function setPlayerNames(names) {
                Scripts.setPlayers(names)
        }

        function highlightPlayer(name, turnIndex) {
                Scripts.highlightRect(name, turnIndex)
        }

        PlayerInfo {
                id: playerOne
                height: 64
                width: parent.width / 2
                anchors.left: parent.left
        }

        PlayerInfo {
                id: playerTwo
                height: 64
                anchors.left: playerOne.right
                anchors.right: parent.right
        }

        TurnPointer {
                id: turnPointer
                anchors.top: playerOne.bottom
                anchors.topMargin: 2
                x: Scripts.centerXOf(playerOne)
        }
}
