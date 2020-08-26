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

    QtObject{
        id: buttonTextContainer
        property string startText: qsTr("Start")
        property string pauseText: qsTr("Pause")
        property string restartText: qsTr("Restart")
        property string resumeText: qsTr("Resume")
    }

    QtObject{
        id: currentTournamentMetaData
        property string tournamentTitle: ""
        property int tournamentGameMode: 0
        property int tournamentKeyPoint: 0
    }

    function appendScore(player,point,score)
    {
        if(currentTournamentMetaData.tournamentGameMode === 0x1)
            firstToPostScoreTable.appendData(player,point,score);
    }
    function takeScore(player)
    {
        if(currentTournamentMetaData.tournamentGameMode === 0x1)
            firstToPostScoreTable.takeData(player);
    }

    function handlemetaInformation(meta){
        var title = meta[0];
        var gameMode = meta[1];
        var keyPoint = meta[2];
        var assignedPlayerNames = meta[3];

        currentTournamentMetaData.tournamentTitle = title;
        currentTournamentMetaData.tournamentGameMode = gameMode;
        currentTournamentMetaData.tournamentKeyPoint = keyPoint;

        if(gameMode === 0x1)
            initializeFirstToPost(title,keyPoint,assignedPlayerNames);
    }

    function initializeFirstToPost(title,keyPoint,assignedPlayerNames)
    {
        for(var i = 0; i < assignedPlayerNames.length;i++)
        {
            var assignedPlayerName = assignedPlayerNames[i];
            firstToPostScoreTable.appendHeader(assignedPlayerName);
            firstToPostScoreTable.appendData(assignedPlayerName,0,keyPoint);
        }
        requestSetPageTitle(title);
        firstToPostScoreTable.visible = true;
        firstToPostScoreTable.displayPoints = true;
        firstToPostScoreTable.setMinimumColumnsCount(4);
        requestScoreBoardData();
    }

    onReplyFromBackendRecieved: {
        var buttonText = turnNavigator.startButtonText, playerName, scoreValue;
        if(response === 0x12) // Gamecontroller is stopped
        {
            keyPad.enableKeys = false;
            turnNavigator.startButtonText = buttonTextContainer.resumeText;
        }
        else if(response === 0x2D) // Gamecontroller is ready and awaits input
        {
            turnNavigator.startButtonText = buttonTextContainer.pauseText;

            var canUndo = args[0];
            var canRedo = args[1];
            var currentRoundIndex = args[2];
            var currentPlayerUserName = args[3];
            var throwSuggestion = args[4];

            suggestText.text = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;

            turnNavigator.updateState(currentRoundIndex,currentPlayerUserName,canUndo,canRedo);

            keyPad.enableKeys = true;
        }
        else if(response === 0x10) // Backend replies end of transmission
        {
            turnNavigator.startButtonEnabled = true;
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
            keyPad.enableKeys = false;
            var winnerPlayerName = args[0];
            turnNavigator.updateState(turnNavigator.currentRoundIndex,turnNavigator.currentPlayer,false,false);
            winnerText.text = textSourceContainer.winnerLabel + winnerPlayerName;
            turnNavigator.startButtonText = buttonTextContainer.restartText;

        }
        else if(response === 0x17)
        {
            turnNavigator.startButtonEnabled = true;
        }
    }

    signal sendInput(int value, int modifier)

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
                if(buttonText === buttonTextContainer.startText || buttonText === buttonTextContainer.resumeText)
                    requestStart();
                else if(buttonText === buttonTextContainer.restartText)
                {
                    requestRestart();
                    firstToPostScoreTable.clearTable();
                    body.requestScoreBoardData();
                    firstToPostScoreTable.setMinimumColumnsCount(4);
                    keyPad.enableKeys = false;
                    turnNavigator.startButtonText = buttonTextContainer.startText;
                    turnNavigator.currentRoundIndex = 0;
                    turnNavigator.currentPlayer = "";
                }
                else
                    requestStop();
            }
            onLeftButtonClicked: requestUndo()
            onRightButtonClicked: requestRedo()
        }
        ScoreBoard{
            id: firstToPostScoreTable
            color: "transparent"
            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true
            Layout.minimumHeight: 128
            scoreFontSize: 20
            pointFontSize: 10
            visible: false
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
                enableKeys = false;
                if(turnNavigator.startButtonText === buttonTextContainer.restartText)
                    turnNavigator.startButtonText = buttonTextContainer.pauseText;
                body.sendInput(val,modifierCode);
            }
            enableKeys: false
        }
    }
    Component.onCompleted: {
        body.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
        applicationInterface.sendTournamentMetaData.connect(body.handlemetaInformation);
        body.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
        applicationInterface.sendPlayerScore.connect(body.appendScore);
        body.requestStart.connect(applicationInterface.handleRequestStart);
        body.requestStop.connect(applicationInterface.handleRequestStop);
        body.requestRestart.connect(applicationInterface.handleRestartTournament);
        body.sendInput.connect(applicationInterface.handleUserInput);
        body.requestUndo.connect(applicationInterface.requestUndo);
        body.requestRedo.connect(applicationInterface.requestRedo);
        body.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
        requestMetaInformation();
    }
    Component.onDestruction: {
        body.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
        applicationInterface.sendTournamentMetaData.disconnect(body.handlemetaInformation);
        applicationInterface.sendPlayerScore.disconnect(firstToPostScoreTable.appendData);
        body.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
        body.requestStart.disconnect(applicationInterface.handleRequestStart);
        body.requestStop.disconnect(applicationInterface.handleRequestStop);
        body.sendInput.disconnect(applicationInterface.handleUserInput);
        body.requestUndo.disconnect(applicationInterface.requestUndo);
        body.requestRedo.disconnect(applicationInterface.requestRedo);
        body.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    }
}
