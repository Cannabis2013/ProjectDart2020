import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: body
    signal startButtonClicked
    signal leftButtonClicked
    signal rightButtonClicked

    property string startButtonText: "start"
    onStartButtonTextChanged: startButton.text = startButtonText

    property int currentRoundIndex: 0
    property string currentPlayer: ""

    onCurrentRoundIndexChanged: currentRoundLabel.text = textBeholder.currentRoundText + currentRoundIndex
    onCurrentPlayerChanged: currentPlayerLabel.text = currentPlayer

    function refreshTurnKeys()
    {
        leftButton.enabled = localDart.undoPossible();
        rightButton.enabled = localDart.redoPossible();
    }

    QtObject{
        id: textBeholder

        property string currentRoundText: qsTr("Current round: ")
        property string currentPlayerText: qsTr("Current player: ")
    }

    GridLayout{

        anchors.fill: parent

        flow: GridLayout.LeftToRight

        PushButton{
            id: startButton
            text: body.startButtonText
            textColor: "white"
            backgroundColor: "green"
            fontSize: 16
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            width: 80
            height: 32
            onClicked: startButtonClicked()
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
            hoverEnabled: false
            onClicked: leftButtonClicked()
            Layout.alignment: Qt.AlignVCenter

            enabled: false;
        }

        GridLayout{
            Layout.maximumWidth: 128

            Layout.preferredHeight: 64

            flow: GridLayout.TopToBottom

            Label{
                id: currentRoundLabel

                Layout.fillWidth: true
                Layout.fillHeight: true

                text: textBeholder.currentRoundText + currentRoundIndex
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
            hoverEnabled: false
            onClicked: rightButtonClicked()

            Layout.alignment: Qt.AlignVCenter

            enabled: false
        }

        Rectangle{
            Layout.fillWidth: true
        }
    }
}
