import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "dpcinit.js" as Initialize
import "dpcscripts.js" as DPCScripts
import "dpscstatescripts.js" as DPCStateScripts

Page {
        id: dpcContent

        signal backButtonClicked

        header: Button {
                text: qsTr("Back")
                onClicked: backButtonClicked()
        }

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                TurnController {
                        id: dpcTurnController
                        Layout.fillWidth: true
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        Layout.alignment: Qt.AlignHCenter
                        onStart: DPCScripts.startGame()
                        onPause: dpcContent.state = "stopped"
                        onResume: dpcContent.state = "waitingForInput"
                        onRestart: DPCScripts.resetTournament()
                        onUndo: DPCScripts.undoClicked()
                        onRedo: DPCScripts.redoClicked()
                }
                DPCBoard {
                        id: dpcScoreBoard
                        Layout.minimumWidth: dpcContent.width * 0.8
                        Layout.maximumWidth: dpcContent.width * 0.8
                        Layout.alignment: Qt.AlignHCenter
                }
                KeyDataDisplay {
                        id: keyDataDisplay
                        Layout.fillWidth: true
                }
                DPSCKeyPad {
                        id: pointKeyPad
                        Layout.alignment: Qt.AlignBottom
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onSendInput: DPCScripts.handleScoreKeyPadInput(value,
                                                                       keyCode)
                }
        }
        states: [
                State {
                        name: "winner"
                        StateChangeScript {
                                script: DPCStateScripts.declareWinner()
                        }
                },
                State {
                        name: "stopped"
                        StateChangeScript {
                                script: DPCStateScripts.backendIsStopped()
                        }
                },
                State {
                        name: "ready"
                        StateChangeScript {
                                script: dpcTurnController.ready()
                        }
                },
                State {
                        name: "waitingForInputConfirmation"
                        StateChangeScript {
                                script: DPCStateScripts.backendProcessesInput()
                        }
                },
                State {
                        name: "waitingForInput"
                        StateChangeScript {
                                script: DPCStateScripts.backendAwaitsInput()
                        }
                }
        ]
        Component.onCompleted: Initialize.init()
}
