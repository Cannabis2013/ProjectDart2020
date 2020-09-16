import QtQuick 2.0
import QtQuick.Layouts 1.3

/*
  Controller status table:
    -> GameControllerIdle = 0x9
    -> GamecontrollerBusy = 0xa
    -> GameControllerStopped = 0xb
    -> GameControllerAwaitsInput = 0xc
    -> GameControllerRunning = 0xd
    -> GameControllerWinnerDeclared = 0xe
    -> GameControllerNotInitialized = 0xf
  */

Content {
    id: body
    color: "transparent"

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

    function appendScore(player,point,score)
    {
        if(currentTournamentMetaData.tournamentGameMode === 0x1)
            tableLoader.item.appendData(player,point,score);
    }
    function takeScore(player)
    {
        if(currentTournamentMetaData.tournamentGameMode === 0x1)
            tableLoader.item.takeData(player);
    }

    function handleMetaInformation(meta){
        currentTournamentMetaData.tournamentTitle = meta[0];
        currentTournamentMetaData.tournamentGameMode = meta[1];
        currentTournamentMetaData.tournamentKeyPoint = meta[2];
        currentTournamentMetaData.assignedPlayers = meta[3];;
        currentTournamentMetaData.determinedWinner = meta[4];
        if(currentTournamentMetaData.tournamentGameMode === 0x1)
            tableLoader.sourceComponent = firstToPostTableComponent;
    }

    function tableLoaded()
    {
        var gameMode = currentTournamentMetaData.tournamentGameMode;
        if(gameMode === 0x1)
            initializeFirstToPost();
    }

    function initializeFirstToPost()
    {
        var title = currentTournamentMetaData.tournamentTitle;
        var assignedPlayers = currentTournamentMetaData.assignedPlayers;
        var keyPoint = currentTournamentMetaData.tournamentKeyPoint;
        for(var i = 0; i < assignedPlayers.length;i++)
        {
            var assignedPlayerName = assignedPlayers[i];
            tableLoader.item.appendHeader(assignedPlayerName);
            tableLoader.item.appendData(assignedPlayerName,0,keyPoint);
        }
        requestSetPageTitle(title);
        tableLoader.item.displayPoints = true;
        tableLoader.item.setMinimumColumnsCount(4);
        requestScoreBoardData();
    }

    function handleBackendIsReadyAndAwaitsInput(args)
    {
        var canUndo = args[0];
        var canRedo = args[1];
        var currentRoundIndex = args[2];
        var currentPlayerUserName = args[3];
        var throwSuggestion = args[4];

        suggestText.text = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
        turnNavigator.updateState(currentRoundIndex,currentPlayerUserName,canUndo,canRedo);
        body.state = "waitingForInput";
    }

    onReplyFromBackendRecieved: {
        var buttonText = turnNavigator.startButtonText, playerName, scoreValue;
        if(response === 0x12) // Gamecontroller is stopped
        {
            body.state = "stopped";
        }
        else if(response === 0x2D) // Gamecontroller is ready and awaits input
        {
            var canUndo = args[0];
            var canRedo = args[1];
            var currentRoundIndex = args[2];
            var currentPlayerUserName = args[3];
            var throwSuggestion = args[4];

            suggestText.text = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
            turnNavigator.updateState(currentRoundIndex,currentPlayerUserName,canUndo,canRedo);
            body.state = "waitingForInput";
        }
        else if(response === 0x10) // Backend replies end of transmission
        {
            if(currentTournamentMetaData.determinedWinner !== "")
                body.state = "winner";
            else
                body.state = "ready";
        }

        else if(response === 0x45) // Backend is initialized and ready
        {
            turnNavigator.startButtonEnabled = true;
        }
        /*
          Backend responds that it has updated its datacontext
          */
        else if(response == 0x27) // Controller is in AddScoreState
        {
            playerName = args[0];
            var pointValue = args[1];
            scoreValue = args[2];
            appendScore(playerName,pointValue,scoreValue);
            requestStatusFromBackend();
        }

        else if(response == 0x28) // Controller is in UndoState
        {
            playerName = args[0];
            takeScore(playerName);
            requestStatusFromBackend();
        }
        else if(response === 0x15) // Winner declared
        {
            currentTournamentMetaData.determinedWinner = args[0];
            body.state = "winner";

        }
        else if(response === 0x17)
        {
            turnNavigator.startButtonEnabled = true;
        }
    }
    /*
      Here I define all the tables for each corresponding gamemode
      */
    Component{
        id: firstToPostTableComponent
        FirstToPostTable{}
    }

    GridLayout{
        id: componentLayout
        anchors.fill: parent
        columns: 1
        flow: GridLayout.TopToBottom
        TurnNavigationComponent{
            id: turnNavigator
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            startButtonEnabled: false
            startButtonEnablePressAndHold: true
            onStartButtonPressAndHoldClicked: {
                turnNavigator.startButtonText = buttonTextContainer.restartText;
            }

            onStartButtonClicked: {
                var buttonText = turnNavigator.startButtonText;
                if(buttonText === buttonTextContainer.startText ||
                        buttonText === buttonTextContainer.resumeText)
                    requestStart();
                else if(buttonText === buttonTextContainer.restartText)
                    body.state = "restart";
                else
                {
                    body.state = "pauseState";
                    requestStop();
                }
            }
            onLeftButtonClicked: {
                body.state = "waitingForInputConfirmation";
                requestUndo();
            }

            onRightButtonClicked: {
                body.state = "waitingForInputConfirmation";
                requestRedo();
            }
        }

        Loader{
            id: tableLoader
            Layout.fillWidth: true
            Layout.minimumHeight: 128
        }

        GridLayout{
            flow: GridLayout.TopToBottom
            Layout.maximumHeight: 40
            Layout.fillWidth: true
            Text {
                id: winnerText
                text: qsTr(textSourceContainer.winnerLabel)
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pointSize: 16
                Layout.alignment: Qt.AlignBottom
            }
            Text {
                id: suggestText
                text: qsTr(textSourceContainer.throwSuggestLabel)
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pointSize: 16
                Layout.alignment: Qt.AlignTop
            }
            Rectangle{
                Layout.fillHeight: true
            }
        }

        KeyPadComponent{
            id: keyPad
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 128
            Layout.maximumHeight: 384
            Layout.alignment: Qt.AlignBottom
            onKeyClicked: {
                body.state = "waitingForInputConfirmation";
                body.sendInput(val,modifierCode);
            }
            enableKeys: false
        }
    }
    states: [
        State {
            name: "winner"
            PropertyChanges {
                target: keyPad
                enableKeys : false
            }
            PropertyChanges {
                target: turnNavigator
                startButtonText : buttonTextContainer.restartText
                startButtonEnabled : enabled
            }
            StateChangeScript{
                script: {
                    turnNavigator.updateState(turnNavigator.currentRoundIndex,
                                              turnNavigator.currentPlayer,
                                              false,
                                              false);
                    winnerText.text = textSourceContainer.winnerLabel +
                            " " +
                            currentTournamentMetaData.determinedWinner;
                }
            }
        },
        State {
            name: "stopped"
            PropertyChanges {
                target: keyPad
                enableKeys : false
            }
            PropertyChanges {
                target: turnNavigator
                startButtonText : buttonTextContainer.resumeText
                startButtonEnabled : true
                undoButtonEnabled : false
                redoButtonEnabled : false
            }
        },
        State {
            name: "ready"
            PropertyChanges {
                target: turnNavigator
                startButtonEnabled : true
                startButtonText : buttonTextContainer.startText
            }
        },
        State {
            name: "restart"
            PropertyChanges {
                target: turnNavigator
                startButtonText : buttonTextContainer.startText;
                currentRoundIndex : 0;
                currentPlayer : "";
                undoButtonEnabled : false
                redoButtonEnabled : false
            }
            PropertyChanges {
                target: keyPad
                enableKeys : false
            }
            StateChangeScript{
                script: {
                    tableLoader.sourceComponent = undefined;
                    body.requestRestart();
                }
            }
        },
        State {
            name: "waitingForInputConfirmation"
            PropertyChanges {
                target: keyPad
                enableKeys: false
            }
            PropertyChanges {
                target: turnNavigator
                startButtonText : buttonTextContainer.waitText
                undoButtonEnabled : false
                redoButtonEnabled : false
            }
        },
        State {
            name: "waitingForInput"
            PropertyChanges {
                target: turnNavigator
                startButtonEnabled : true
                startButtonText : buttonTextContainer.pauseText
            }
            PropertyChanges {
                target: keyPad
                enableKeys : true
            }
        }
    ]
    Component.onCompleted: {
        body.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
        applicationInterface.sendTournamentMetaData.connect(body.handleMetaInformation);
        body.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
        applicationInterface.sendPlayerScore.connect(body.appendScore);
        body.requestStart.connect(applicationInterface.handleRequestStart);
        body.requestStop.connect(applicationInterface.handleRequestStop);
        body.requestRestart.connect(applicationInterface.handleRestartTournament);
        body.sendInput.connect(applicationInterface.handleUserInput);
        body.requestUndo.connect(applicationInterface.handleUndoRequest);
        body.requestRedo.connect(applicationInterface.handleRedoRequest);
        body.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
        tableLoader.loaded.connect(body.tableLoaded);
        requestMetaInformation();
    }
    Component.onDestruction: {
        body.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
        applicationInterface.sendTournamentMetaData.disconnect(body.handleMetaInformation);
        body.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
        applicationInterface.sendPlayerScore.disconnect(body.appendScore);
        body.requestStart.disconnect(applicationInterface.handleRequestStart);
        body.requestStop.disconnect(applicationInterface.handleRequestStop);
        body.requestRestart.disconnect(applicationInterface.handleRestartTournament);
        body.sendInput.disconnect(applicationInterface.handleUserInput);
        body.requestUndo.disconnect(applicationInterface.requestUndo);
        body.requestRedo.disconnect(applicationInterface.requestRedo);
        body.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
        tableLoader.loaded.disconnect(body.tableLoaded);
    }
}
