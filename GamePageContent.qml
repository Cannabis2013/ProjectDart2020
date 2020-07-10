import QtQuick 2.0
import QtQuick.Layouts 1.3
import "gamePageContentScripts.js" as GamePageScripts

Content {
    color: "transparent"
    clip: true
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
            onStartButtonClicked: {
                var status = localDart.gameStatus();
                if(status === 0xc) // 0xc = idle
                {
                    localDart.startGame();
                    startButtonText = "Pause";
                    keyPad.enableKeys = true;
                }
                else if(status === 0xe) // 0xe = running
                {

                    localDart.stopGame();
                    startButtonText = "Resume";
                    keyPad.enableKeys = false;
                }
                else if(status === 0x10) // 0x10 = WinnerDeclared
                {
                    startButtonText = "Restart";
                    keyPad.enableKeys = false;
                }
            }
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
        GamePageScripts.initializeScoreBoard();
    }
}
