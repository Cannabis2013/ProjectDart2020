import QtQuick 2.0
import QtQuick.Layouts 1.3
import "gamePageScripts.js" as GameScripts

Content {
    id: body
    QtObject{
        id: textSourceContainer
        property string throwSuggestLabel: "Suggested target row:"
        property string winnerLabel: "Winner:"
    }
    onBackButtonPressed: requestStop()
    signal requestMetaInformation
    signal requestScoreBoardData
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    signal requestUndo
    signal requestRedo
    signal sendInput(int value, int modifier)


    signal scoreRecieved(string playerName, int point, int score, int keyCode)
    QtObject{
        id: buttonTextContainer
        property string startText: qsTr("Start")
        property string pauseText: qsTr("Pause")
        property string restartText: qsTr("Restart")
        property string resumeText: qsTr("Resume")
        property string waitText: qsTr("Wait")
    }
    QtObject{
        id: currentTournamentMetaData
        property string tournamentTitle: ""
        property int tournamentGameMode: 0
        property int tournamentKeyPoint: 0
        property string determinedWinner: ""
        property var assignedPlayers: []
    }
    /*
      Handle reply from backend:
      */
    onReplyFromBackendRecieved: GameScripts.handleReplyFromBackend(response,args)

    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        Loader{
            id: turnControllerItemSlot
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
        }
        Loader{
            id: scoreBoardItemSlot
            Layout.fillWidth: true
            Layout.minimumHeight: 128
        }
        Loader{
            id: notificationItemSlot
            Layout.fillWidth: true
            Layout.maximumHeight: 40
        }
        Loader{
            id: keyPaditemSlot
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: 384
            Layout.minimumHeight: 128
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.restartText;
                    turnControllerItemSlot.item.startButtonEnabled = true;
                    var currentPlayer = turnControllerItemSlot.item.currentPlayer;
                    turnControllerItemSlot.item.updateState(turnNavigator.currentRoundIndex,
                                              currentPlayer,
                                              false,
                                              false);
                    winnerText.text = textSourceContainer.winnerLabel + " " +
                            currentTournamentMetaData.determinedWinner;
                    keyPaditemSlot.item.enableKeys = false;
                }
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.resumeText;
                    turnControllerItemSlot.item.startButtonEnabled = true;
                    turnControllerItemSlot.item.undoButtonEnabled = false;
                    turnControllerItemSlot.item.redoButtonEnabled = false;
                    keyPaditemSlot.item.enableKeys = false;
                }
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonEnabled = true;
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.startText;
                }
            }
        },
        State {
            name: "restart"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.startText;
                    turnControllerItemSlot.item.currentRoundIndex = 0;
                    turnControllerItemSlot.item.currentPlayer = "";
                    turnControllerItemSlot.item.undoButtonEnabled = false;
                    turnControllerItemSlot.item.redoButtonEnabled = false;
                    keyPaditemSlot.item.enableKeys = false;
                    scoreBoardItemSlot.sourceComponent = undefined;
                    body.requestRestart();
                }
            }
        },
        State {
            name: "preRestart"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.restartText;
                    turnControllerItemSlot.item.startButtonEnabled = true;
                    turnControllerItemSlot.item.undoButtonEnabled = false;
                    turnControllerItemSlot.item.redoButtonEnabled = false;
                    keyPaditemSlot.item.enableKeys = false;
                    body.requestStop();
                }
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.waitText;
                    turnControllerItemSlot.item.undoButtonEnabled = false;
                    turnControllerItemSlot.item.redoButtonEnabled = false;
                    keyPaditemSlot.item.enableKeys = false;
                }
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: {
                    turnControllerItemSlot.item.startButtonText = buttonTextContainer.pauseText;
                    turnControllerItemSlot.item.startButtonEnabled = true;
                    keyPaditemSlot.item.enableKeys = true;
                }
            }
        }
    ]
    Component.onCompleted: {
        GameScripts.connectComponents();
        requestMetaInformation();
    }
    Component.onDestruction: {
        GameScripts.disconnectComponents();
    }
}
