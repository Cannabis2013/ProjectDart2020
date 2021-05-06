import QtQuick 2.0
import QtQuick.Layouts 1.3

/*
  Gamemodes:
    FirstToPost = 0x1,
    RoundLimit =0x2,
    Circular = 0x3,
    Cricket = 0xAA
  */
Content {
    id: gamePageBody
    QtObject{
        id: textSourceContainer
        property string throwSuggestLabel: "Target row:"
        property string winnerLabel: "Winner:"
    }
    signal requestMetaInformation
    signal requestMultiThrowScores
    signal requestSingleThrowScores
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: GameGeneralScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    QtObject{
        id: buttonTextContainer
        readonly property string startText: qsTr("Start")
        readonly property string pauseText: qsTr("Pause")
        readonly property string restartText: qsTr("Restart")
        readonly property string resumeText: qsTr("Resume")
        readonly property string waitText: qsTr("Wait")
    }
    /*
      Tournament metadata property
      */
    property QtObject tournamentMetaData: QtObject{}
    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: multiPointTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
        }
        DartsMultiPointScoreBoard{
            id: multiPointScoreBoard
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
            visible: status === Loader.Ready
        }
        Rectangle{
             color: "transparent"
             height: 5
        }
        PointKeyPad{
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
                    multiPointTurnController.backendHasDeclaredAWinner();
                    keyPadInterface().enableKeyPad(false);
                    GameGeneralScripts.setWinnerText();
                }
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: {
                    multiPointTurnController.backendIsStopped();
                    keyPadInterface().enableKeyPad(false);
                }
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: multiPointTurnController.backendIsReady()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: {
                    multiPointTurnController.backendProcessesInput();
                    keyPadInterface().enableKeyPad(false);
                }
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: {
                    multiPointTurnController.backendAwaitsInput();
                    keyPadInterface().enableKeyPad(true);
                }
            }
        }
    ]
    //Component.onCompleted: GameGeneralScripts.initializeComponent()
    /*
    Component.onDestruction: {
        GameGeneralScripts.disconnectComponents();
        FirstToPostScripts.disconnectFtpInterface();
    }
    */
}
