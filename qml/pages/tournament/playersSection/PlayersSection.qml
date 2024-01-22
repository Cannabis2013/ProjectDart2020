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

        Image {
                id: turnRect

                Behavior on x {
                        NumberAnimation {
                                duration: 200
                        }
                }
                source: "qrc:/pictures/Ressources/Pictures/up_arrow.png"

                height: 32
                width: 32
                anchors.top: playerOne.bottom
                anchors.topMargin: 2
                x: playerOne.x + playerOne.width / 2 - 16
        }
}
