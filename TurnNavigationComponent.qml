import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {

    signal leftButtonClicked
    signal rightButtonClicked

    GridLayout{

        anchors.fill: parent

        flow: GridLayout.LeftToRight

        DecoratedButtonComponent{
            id: leftButton

            width: 64
            height: 64

            source: "qrc:/pictures/Ressources/arrow.png"

            orientation: 0x1

            onClicked: leftButtonClicked()
        }

        GridLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            flow: GridLayout.TopToBottom

            Label{

            }
        }

        DecoratedButtonComponent{
            id: rightButton

            width: 64
            height: 64

            source: "qrc:/pictures/Ressources/arrow.png"

            onClicked: rightButtonClicked()
        }
    }
}
