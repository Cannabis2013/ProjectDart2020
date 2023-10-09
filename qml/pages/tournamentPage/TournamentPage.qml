import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/tournament/turn"
import "../../components/tournament/players"
import "../../components/tournament/keyPad"
import "../../components/pages"
import "../../components/buttons"
import "tournamentPageScripts.js" as PageScripts

BlackPage {
        id: tournamentPage

        buttonText: "Menu"
        pageTitle: "Tournament"

        onBackClicked: {
                dartsController.saveState()
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                PlayerScores {
                        id: scoresView
                        height: Layout.fillHeight = true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                TurnInformation {
                        id: turnInfoComp
                        Layout.alignment: Qt.AlignHCenter
                        height: 32
                        width: 262
                        onUndoClicked: {
                                const response = dartsController.undoTurn()
                                PageScripts.updatePlayerScores(response)
                                PageScripts.updateTurnInfo()
                        }
                        onRedoClicked: {
                                const response = dartsController.redoTurn()
                                PageScripts.updatePlayerScores(response)
                                PageScripts.updateTurnInfo()
                        }
                }

                Text {
                        id: statistics
                        Layout.fillWidth: true
                        color: "white"
                        height: 64
                        font.pointSize: 20
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: targetRow
                        Layout.fillWidth: true
                        color: "white"
                        height: 32
                        font.pointSize: 32
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                }

                Rectangle {
                        height: 64
                }

                KeyPads {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
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
