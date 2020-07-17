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
        if(status === 0xb) // Gamecontroller is stopped
        {
            buttonText = "Resume"
        }
        else if(status === 0xc) // Gamecontroller awaits input
        {
            turnNavigator.startButtonText = "Pause";
            keyPad.enableKeys = true;
        }
        else if(status === 0xe)
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
            onStartButtonClicked: sendStatusRequest()
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
        localDart.sendAssignedPlayerName.connect(scoreTable.appendHeader);
        localDart.sendPlayerScore.connect(scoreTable.appendData);
        body.requestScoreBoardData.connect(localDart.handleScoreBoardRequest);
        body.requestStart.connect(localDart.requestStart);
        body.requestStop.connect(localDart.requestStop);
        body.sendInput.connect(localDart.addPoint);
        body.sendStatusRequest.disconnect(localDart.handleStatusRequest);

        scoreTable.setMinimumColumnsCount(4);

        requestScoreBoardData();
    }
    Component.onDestruction: {
        localDart.sendAssignedPlayerName.disconnect(scoreTable.appendHeader);
        localDart.sendPlayerScore.disconnect(scoreTable.appendData);
        body.requestScoreBoardData.disconnect(localDart.handleScoreBoardRequest);
        body.requestStart.disconnect(localDart.requestStart);
        body.requestStop.disconnect(localDart.requestStop);
        body.sendInput.disconnect(localDart.addPoint);
    }
}
