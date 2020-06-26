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
        }

        GridLayout{
            Layout.fillWidth: true
            height: 64

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
        }
    }
}
