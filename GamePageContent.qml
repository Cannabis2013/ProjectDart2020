import QtQuick 2.0
import QtQuick.Layouts 1.3
import "gamePageFactory.js" as GamePageFactory
import "fTPScripts.js" as FirstToPostScripts
import "gamePageGeneralScripts.js" as GameGeneralScripts

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
        property string throwSuggestLabel: "Suggested target row:"
        property string winnerLabel: "Winner:"
    }
    signal requestMetaInformation
    signal requestMultiThrowScores
    signal requestSingleThrowScores
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    signal requestUndo
    signal requestRedo
    signal sendInput(int value, int modifier)
    signal scoreRecieved(string playerName, int point, int score, int keyCode)
    signal setupGame()
    onSetupGame: {
        if(tournamentMetaData.tournamentGameMode === 0x1)
            FirstToPostScripts.setupFirstToPostScoreTable();
    }
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
    /*
      Handle reply from backend:
      */
    onReplyFromBackendRecieved: GameGeneralScripts.handleReplyFromBackend(response,args)
    function turnControllerInterface(){
        return turnControllerItemSlot.item;
    }
    function notificationInterface()
    {
        return notificationItemSlot.item;
    }

    function scoreBoardInterface(){
        return scoreBoardItemSlot.item;
    }

    function keyPadInterface()
    {
        return keyPaditemSlot.item;
    }
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
            visible: status === Loader.Ready
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
                    turnControllerInterface().startButtonText = buttonTextContainer.restartText;
                    turnControllerInterface().startButtonEnabled = true;
                    var currentPlayer = turnControllerInterface().currentPlayer;
                    var currentRoundIndex = turnControllerInterface().currentRoundIndex;
                    turnControllerInterface().updateState(currentRoundIndex,
                                              currentPlayer,
                                              false,
                                              false);
                    var winnerName = textSourceContainer.winnerLabel + " " +
                            tournamentMetaData.determinedWinner;
                    keyPadInterface().enableKeyPad(false);
                    GameGeneralScripts.handleSetWinnerText(winnerName);
                }
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: {
                    turnControllerInterface().startButtonText = buttonTextContainer.resumeText;
                    turnControllerInterface().startButtonEnabled = true;
                    turnControllerInterface().undoButtonEnabled = false;
                    turnControllerInterface().redoButtonEnabled = false;
                    keyPadInterface().enableKeyPad(false);
                }
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: {
                    turnControllerInterface().startButtonEnabled = true;
                    turnControllerInterface().startButtonText = buttonTextContainer.startText;
                }
            }
        },
        State {
            name: "preRestart"
            StateChangeScript{
                script: {
                    turnControllerInterface().startButtonText = buttonTextContainer.restartText;
                    turnControllerInterface().startButtonEnabled = true;
                    turnControllerInterface().undoButtonEnabled = false;
                    turnControllerInterface().redoButtonEnabled = false;
                    keyPadInterface().enableKeyPad(false);
                    gamePageBody.requestStop();
                }
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: {
                    turnControllerInterface().startButtonText = buttonTextContainer.waitText;
                    turnControllerInterface().undoButtonEnabled = false;
                    turnControllerInterface().redoButtonEnabled = false;
                    keyPadInterface().enableKeyPad(false);
                }
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: {
                    turnControllerInterface().startButtonText = buttonTextContainer.pauseText;
                    turnControllerInterface().startButtonEnabled = true;
                    keyPadInterface().enableKeyPad(true);
                }
            }
        }
    ]
    Component.onCompleted: GameGeneralScripts.initializeComponent()
    Component.onDestruction: GameGeneralScripts.disconnectComponents()
}
