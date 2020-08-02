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
        property string throwSuggestTitle: "Throw suggestion:"
    }

    onBackButtonPressed: requestStop()

    signal requestScoreBoardData
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    signal requestUndo
    signal requestRedo

    onRequestScoreBoardData: responseTimer.start()

    function appendHeaderItem(item)
    {
        scoreTable.appendHeader(item);
    }
    function appendScore(player,score)
    {
        scoreTable.appendData(player,score);
    }

    onReplyFromBackendRecieved: {
        var buttonText = turnNavigator.startButtonText, playerName, scoreValue;
        if(response === 0x12) // Gamecontroller is stopped
        {
            keyPad.enableKeys = false;
            turnNavigator.startButtonText = "Resume"
        }
        else if(response === 0x2D) // Gamecontroller is ready and awaits input
        {
            turnNavigator.startButtonText = "Pause";

            var canUndo = args[0];
            var canRedo = args[1];
            var currentRoundIndex = args[2];
            var currentPlayerUserName = args[3];
            var throwSuggestion = args[4];

            notificationText.text = textSourceContainer.throwSuggestTitle + " " + throwSuggestion;

            print("Throw suggestion: " + throwSuggestion);

            turnNavigator.updateState(currentRoundIndex,currentPlayerUserName,canUndo,canRedo);

            keyPad.enableKeys = true;
        }
        else if(response === 0x41)
        {
            turnNavigator.startButtonEnabled = true;
        }

        else if(response === 0x17)
        {
            turnNavigator.startButtonEnabled = true;
        }

        else if(response == 0x27) // Controller is in AddScoreState
        {
            playerName = args[0];
            scoreValue = args[1];
            scoreTable.appendData(playerName,scoreValue);
            requestStatusFromBackend();
        }

        else if(response == 0x28) // Controller is in UndoState
        {
            playerName = args[0];
            scoreTable.takeData(playerName);
            requestStatusFromBackend();
        }
        else if(response === 0x3E) // Winner declared
        {
            keyPad.enableKeys = false;
            turnNavigator.startButtonText = "Restart"
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
            height: 64
            Layout.alignment: Qt.AlignHCenter
            startButtonEnabled: false
            startButtonEnablePressAndHold: true
            onStartButtonPressAndHoldClicked: {
                turnNavigator.startButtonText = "Restart"
            }

            onStartButtonClicked: {
                var buttonText = turnNavigator.startButtonText;
                if(buttonText === "Start" || buttonText === "Resume")
                    requestStart();
                else if(buttonText === "Restart")
                {
                    requestRestart();
                    scoreTable.clearTable();
                    body.requestScoreBoardData();
                    scoreTable.setMinimumColumnsCount(4);
                }
                else
                    requestStop();
            }
            onLeftButtonClicked: requestUndo()
            onRightButtonClicked: requestRedo()
        }
        ScoreBoard{
            id: scoreTable
            color: "transparent"
            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true
            height: 125
        }
        Text {
            id: notificationText
            text: qsTr(textSourceContainer.throwSuggestTitle)
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        KeyPadComponent{
            id: keyPad
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 128
            Layout.maximumHeight: 384
            Layout.alignment: Qt.AlignTop
            onKeyClicked: {
                enableKeys = false;
                body.sendInput(val,modifierCode);
            }

            enableKeys: false
        }
    }
    Component.onCompleted: {
        body.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
        applicationInterface.sendAssignedPlayerName.connect(body.appendHeaderItem);
        applicationInterface.sendPlayerScore.connect(body.appendScore);
        body.requestStart.connect(applicationInterface.requestStart);
        body.requestStop.connect(applicationInterface.requestStop);
        body.requestRestart.connect(applicationInterface.handleRestartTournament);
        body.sendInput.connect(applicationInterface.handleUserInput);
        body.requestUndo.connect(applicationInterface.requestUndo);
        body.requestRedo.connect(applicationInterface.requestRedo);
        body.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);

        scoreTable.setMinimumColumnsCount(4);

        requestScoreBoardData();
    }
    Component.onDestruction: {
        applicationInterface.sendAssignedPlayerName.disconnect(scoreTable.appendHeader);
        applicationInterface.sendPlayerScore.disconnect(scoreTable.appendData);
        body.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
        body.requestStart.disconnect(applicationInterface.requestStart);
        body.requestStop.disconnect(applicationInterface.requestStop);
        body.sendInput.disconnect(applicationInterface.handleUserInput);
        body.requestUndo.disconnect(applicationInterface.requestUndo);
        body.requestRedo.disconnect(applicationInterface.requestRedo);
        body.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    }
}
