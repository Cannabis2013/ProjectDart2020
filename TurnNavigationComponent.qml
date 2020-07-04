import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {

    signal leftButtonClicked
    signal rightButtonClicked

    property int currentTurnIndex: 0
    property string currentPlayer: ""

    onCurrentTurnIndexChanged: textBeholder.currentTurnIndexText + currentTurnIndex
    onCurrentPlayerChanged: textBeholder.currentPlayerText + currentPlayer

    QtObject{
        id: textBeholder

        property string currentTurnIndexText: qsTr("Current turn: ")
        property string currentPlayerText: qsTr("Current player: ")
    }

    GridLayout{

        anchors.fill: parent

        flow: GridLayout.LeftToRight

        PushButton{
            id: backButton

            text: "Start"
            textColor: "white"

            backgroundColor: "green"

            fontSize: 16

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            width: 80
            height: 32

            onClicked: {

                var status = localDart.gameStatus();
                if(status === 0xc) // 0xc = idle
                {
                    localDart.startGame();
                    text = "Pause";
                }
                else if(status === 0xe) // 0xe = running
                {
                    localDart.stopGame();
                    text = "Resume";
                }
                else if(status === 0x10) // 0x10 = WinnerDeclared
                {
                    text = "Restart";
                }
            }
        }

        Rectangle{
            Layout.fillWidth: true
        }

        PushButton{
            id: leftButton

            width: 64
            height: 64

            image: "qrc:/pictures/Ressources/arrow.png"

            imageRotation: 180

            imageMargins: 20

            buttonRadius: 45

            hoveredColor: "white"

            onClicked: leftButtonClicked()

            Layout.alignment: Qt.AlignVCenter

            enabled: localDart.undoPossible();
        }

        GridLayout{
            Layout.maximumWidth: 128

            Layout.preferredHeight: 64

            flow: GridLayout.TopToBottom

            Label{
                id: currentTurnLabel

                Layout.fillWidth: true
                Layout.fillHeight: true

                text: textBeholder.currentTurnIndexText + currentTurnIndex
                font.pointSize: 12

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Label{
                id: currentPlayerLabel

                Layout.fillWidth: true
                Layout.fillHeight: true

                text: textBeholder.currentPlayerText + currentPlayer
                font.pointSize: 12

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        PushButton{
            id: rightButton

            width: 64
            height: 64

            image: "qrc:/pictures/Ressources/arrow.png"

            imageMargins: 20

            buttonRadius: 45

            hoveredColor: "white"

            onClicked: rightButtonClicked()

            Layout.alignment: Qt.AlignVCenter

            enabled: localDart.redoPossible()
        }

        Rectangle{
            Layout.fillWidth: true
        }
    }
}
