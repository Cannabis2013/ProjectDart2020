import QtQuick 2.0
import QtQuick.Layouts 1.3

Content {
    id: body
    color: "transparent"
    clip: true

    onBackButtonPressed: localDart.stopGame()

    signal updateInformationDisplay(string currentRound, string currentPlayer, bool canUndo, bool canRedo)

    signal requestScoreBoardData

    function handleStartButtonClicked()
    {

    }

    signal sendInput(int value)

    function handleStatusNotification(status)
    {

    }

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
            onStartButtonClicked: requestStart()
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
            onSendInputValue: sendInput(val)
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
    Component.onCompleted: {
        localDart.sendStatus.connect(handleStatusNotification);
        localDart.sendAssignedPlayerName.connect(scoreTable.appendHeader);
        localDart.sendPlayerScore.connect(scoreTable.appendData);
        localDart.sendInformalControllerValues.connect(turnNavigator.updateState);
        localDart.sendCurrentTournamentKeyPoint.connect(scoreTable.setInitialValue);
        body.requestScoreBoardData.connect(localDart.handleScoreBoardRequest);
        scoreTable.setMinimumColumnsCount(4);
        requestScoreBoardData();
    }
}
