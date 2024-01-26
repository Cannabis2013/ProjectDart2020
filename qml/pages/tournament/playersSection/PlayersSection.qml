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
                height: 56
                width: parent.width / 2
                anchors.left: parent.left
        }

        PlayerInfo {
                id: playerTwo
                height: 56
                anchors.left: playerOne.right
                anchors.right: parent.right
        }

        TurnSlider {
                id: turnPointer
                anchors.top: playerOne.bottom
                x: 0
                width: parent.width
                height: 40
                Component.onCompleted: turnPointer.move(Scripts.centerXOf(playerOne))
        }
}
