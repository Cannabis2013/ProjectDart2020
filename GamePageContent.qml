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
    clip: true

    onBackButtonPressed: requestStop()

    signal requestScoreBoardData
    signal sendStatusRequest
    signal requestStart
    signal requestStop

    onSendStatusRequest: {
        var buttonText = turnNavigator.startButtonText;
        if(buttonText === "Start" || buttonText === "Resume")
            requestStart();
        else
            requestStop();
    }

    onReplyFromBackendRecieved: {
        var buttonText = turnNavigator.startButtonText;
        if(status === 0x12) // Gamecontroller is stopped
        {
            buttonText = "Resume"
        }
        else if(status === 0x13) // Gamecontroller awaits input
        {
            turnNavigator.startButtonText = "Pause";

            var canUndo = args[0];
            var canRedo = args[1];
            var currentRoundIndex = args[2];
            var currentPlayerUserName = args[3];

            turnNavigator.updateState(currentRoundIndex,currentPlayerUserName,canUndo,canRedo);

            keyPad.enableKeys = true;
        }
        else if(status === 0x15) // Winner declared
        {
            keyPad.enableKeys = false;

        }
    }

    signal sendInput(int value)

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
            onStartButtonClicked: body.sendStatusRequest()
        }
        ScoreBoard{
            id: scoreTable
            color: "transparent"
            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true
            height: 125
        }
        Rectangle{
            Layout.minimumHeight: 25
            Layout.maximumHeight: 25
        }
        KeyPadComponent{
            id: keyPad
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 128
            Layout.maximumHeight: 384
            Layout.alignment: Qt.AlignTop
            onSendInputValue: {
                enableKeys = false;
                sendInput(val);
            }

            enableKeys: false
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
    Component.onCompleted: {
        applicationInterface.sendAssignedPlayerName.connect(scoreTable.appendHeader);
        applicationInterface.sendPlayerScore.connect(scoreTable.appendData);
        body.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
        body.requestStart.connect(applicationInterface.requestStart);
        body.requestStop.connect(applicationInterface.requestStop);
        body.sendInput.connect(applicationInterface.addPoint);
        body.sendStatusRequest.connect(applicationInterface.requestGameStatus);

        scoreTable.setMinimumColumnsCount(4);

        requestScoreBoardData();
    }
    Component.onDestruction: {
        applicationInterface.sendAssignedPlayerName.disconnect(scoreTable.appendHeader);
        applicationInterface.sendPlayerScore.disconnect(scoreTable.appendData);
        body.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
        body.requestStart.disconnect(applicationInterface.requestStart);
        body.requestStop.disconnect(applicationInterface.requestStop);
        body.sendInput.disconnect(applicationInterface.addPoint);
        body.sendStatusRequest.disconnect(applicationInterface.requestGameStatus);
    }
}
