import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/playerIcons"
import "../../components/playerScores"
import "../../components/pages"

BlackPage {
        id: tournamentPage
        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                PlayerIcons {
                        id: playerIcons
                        height: 40
                        width: 256
                        Layout.alignment: Qt.AlignHCenter
                }

                PlayerScores {
                        id: scoresView
                        height: 80
                        width: 256
                        Layout.alignment: Qt.AlignHCenter
                }

                Rectangle {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        width: 24
                        color: "white"
                }
        }

        Component.onCompleted: {
                const names = dartsController.playerNames()
                playerIcons.setIconLabels(names)
                scoresView.setNames(names)
        }
}
