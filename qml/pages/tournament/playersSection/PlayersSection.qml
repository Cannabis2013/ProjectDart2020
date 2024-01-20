import QtQuick 2.0
import QtQuick.Layouts 1.3
import "playersSection.js" as Scripts

Item {
        function setPlayerNames(names) {
                Scripts.setPlayers(names)
        }

        function highlightPlayer(name, turnIndex) {
                Scripts.highlightRect(name, turnIndex)
        }

        RowLayout {
                id: playerRects
                anchors.fill: parent
                spacing: 0
                PlayerInfo {
                        id: playerOne
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }

                PlayerInfo {
                        id: playerTwo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }
        }
}
