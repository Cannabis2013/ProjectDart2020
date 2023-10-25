import QtQuick 2.0
import QtQuick.Layouts 1.3
import "./turn"
import "./players"
import "./keyPad"
import "../templates"
import "tournamentPageScripts.js" as PageScripts

PageWithHeader {
        id: tournamentPage

        buttonText: "Menu/Restart"
        pageTitle: "Tournament"

        onBackClicked: dartsController.saveState()
        onBackLongClicked: PageScripts.restartGame()

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                PlayerScores {
                        id: scoresView
                        height: 180
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                TurnInformation {
                        id: turnInfoComp
                        Layout.alignment: Qt.AlignHCenter
                        height: 32
                        Layout.fillWidth: true
                        onUndoClicked: PageScripts.undo()
                        onRedoClicked: PageScripts.redo()
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
                        onReportScore: (modId, point) => {
                                               dartsController.addInput(modId, point)
                                               PageScripts.updateTurnInfo()
                                       }
                        onBustTurn: value => {
                                            dartsController.skipTurn()
                                            PageScripts.updateTurnInfo()
                                    }
                }
        }

        WinnerModal {
                id: winnerModal
                visible: false
                onRestartClicked: PageScripts.restartGame()
                onUndoClicked: PageScripts.undo()
        }

        Component.onCompleted: {
                PageScripts.updateInitialValues()
                PageScripts.updateTurnInfo()
        }
}
