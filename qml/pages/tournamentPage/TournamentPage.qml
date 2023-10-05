import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/playerIcons"
import "../../components/playerScores"
import "../../components/pages"
import "../../components/buttons"
import "../../components/keyPad"
import "tournamentPageScripts.js" as PageScripts

BlackPage {
        id: tournamentPage

        buttonText: "Menu"
        pageTitle: "Tournament"

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
                        width: 262
                        Layout.alignment: Qt.AlignHCenter
                }

                TurnInformation {
                        id: turnInfoComp
                        Layout.alignment: Qt.AlignHCenter
                        height: 32
                        width: 262
                        onUndoClicked: {
                                const response = dartsController.undoTurn()
                                PageScripts.updatePlayerScore(response)
                                PageScripts.updateTurnInfo()
                        }
                        onRedoClicked: {
                                const response = dartsController.redoTurn()
                                PageScripts.updatePlayerScore(response)
                                PageScripts.updateTurnInfo()
                        }
                }

                Rectangle {
                        height: 128
                        Layout.fillHeight: true
                }

                KeyPads {
                        id: keyPad
                        width: 700
                        height: 700
                        Layout.alignment: Qt.AlignHCenter
                        onReportScore: {
                                const response = PageScripts.sendScore(modId, point)
                                PageScripts.updatePlayerScore(response)
                                PageScripts.updateTurnInfo()
                        }
                }
        }

        Component.onCompleted: {
                PageScripts.updateInitialValues()
                PageScripts.updateTurnInfo()
        }
}
