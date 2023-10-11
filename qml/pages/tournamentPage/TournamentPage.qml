import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/tournament/turn"
import "../../components/tournament/players"
import "../../components/tournament/keyPad"
import "../../components/pages"
import "../../components/buttons"
import "tournamentPageScripts.js" as PageScripts

BlackPageWithHeader {
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
                        Layout.fillWidth: true
                        onUndoClicked: {
                                const response = dartsController.undoTurn()
                                PageScripts.updateTurnInfo()
                        }
                        onRedoClicked: {
                                const response = dartsController.redoTurn()
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

                KeyPads {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onReportScore: {
                                dartsController.addInput(modId, point)
                                PageScripts.updateTurnInfo()
                        }
                }
        }

        Component.onCompleted: {
                PageScripts.updateInitialValues()
                PageScripts.updateTurnInfo()
        }
}
