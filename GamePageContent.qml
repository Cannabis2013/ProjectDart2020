import QtQuick 2.0
import QtQuick.Layouts 1.3
import "gamePageContentScripts.js" as GamePageScripts

Content {
    color: "transparent"
    clip: true

    onBackButtonPressed: localDart.stopGame()

    signal updatePlayerScore(string playerName, int score)
    onUpdatePlayerScore: scoreTable.appendData(playerName,score)

    signal updateInformationDisplay(string currentRound, string currentPlayer, bool canUndo, bool canRedo)

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
            onStartButtonClicked: GamePageScripts.initializeFromGameStatus()
            onLeftButtonClicked: GamePageScripts.handleUndo()
            onRightButtonClicked: GamePageScripts.handleRedo()
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
            onEmitScore: GamePageScripts.handleInput(val)
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
    Component.onCompleted: {
        localDart.sendPlayerScore.connect(updatePlayerScore);
    }
}
