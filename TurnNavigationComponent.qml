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

            backgroundColor: "green"

            fontSize: 16

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            width: 96
            height: 48

            onClicked: {

                var status = projectDart.gameStatus();
                if(status === 0xc) // 0xc = idle
                {
                    projectDart.startGame();
                    text = "Pause";


                }
                else if(status === 0xe) // 0xe = running
                {
                    projectDart.stopGame();
                    text = "Resume";
                }
                else if(status === 0x10) // 0x10 = WinnerDeclared
                {
                    text = "Restart";
                }

                /*
                    TODO: Check current game status and implement according to status
                 */
            }
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

            enabled: false
        }

        GridLayout{
            Layout.fillWidth: true
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

            enabled: false
        }
    }
}
