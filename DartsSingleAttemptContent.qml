import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartsSingleAttemptPointScripts.js" as DartsSingleAttemptScripts

/*
  Gamemodes:
    FirstToPost = 0x1,
    RoundLimit =0x2,
    Circular = 0x3,
    Cricket = 0xAA
  */
Content {
    id: dartsSingleAttemptBody
    QtObject{
        id: textSourceContainer
        property string throwSuggestLabel: "Target row:"
        property string winnerLabel: "Winner:"
    }
    signal requestControllerValues
    signal requestSingleAttemptPoints
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: DartsSingleAttemptScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    /*
      Tournament metadata property
      */
    QtObject{
        id: dartsSingleAttemptValues
        property string title: ""
        property int keyPoint: 501
        property int attempts: 3
        property string winnerName: ""
        property var assignedPlayerNames: []
    }

    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: singleAttemptTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: requestStart()
            onResumeButtonClicked: requestStart()
            onPauseButtonClicked: requestStop()
            onRestartButtonClicked: requestRestart()
            onLeftButtonClicked: DartsSingleAttemptScripts.undoClicked()
            onRightButtonClicked: DartsSingleAttemptScripts.redoClicked()
        }
        DartsPointScoreBoard{
            id: pointScoreBoard
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 160

        }
        MyRectangle{
            Layout.fillHeight: true
        }

        KeyDataDisplay{
            id: notificationItemSlot
            Layout.fillWidth: true
            Layout.maximumHeight: 40
        }
        Rectangle{
             color: "transparent"
             height: 5
        }
        PointKeyPad{
            id: pointKeyPad
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
                    singleAttemptTurnController.backendHasDeclaredAWinner();
                    pointKeyPad.enableKeyPad(false);
                    DartsSingleAttemptScripts.setWinnerText();
                }
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: {
                    singleAttemptTurnController.backendIsStopped();
                    pointKeyPad.enableKeyPad(false);
                }
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: singleAttemptTurnController.backendIsReady()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: {
                    singleAttemptTurnController.backendProcessesInput();
                    pointKeyPad.enableKeyPad(false);
                }
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: {
                    singleAttemptTurnController.backendAwaitsInput();
                    pointKeyPad.enableKeyPad(true);
                }
            }
        }
    ]
    Component.onCompleted: DartsSingleAttemptScripts.initializeComponent()
    Component.onDestruction: DartsSingleAttemptScripts.disConnectInterface();
}
