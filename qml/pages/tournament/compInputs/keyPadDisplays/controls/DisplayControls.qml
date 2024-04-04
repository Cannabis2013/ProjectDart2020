import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
        signal clearClicked
        signal removeClicked

        Button {
                id: removeButton
                height: 32
                width: 70
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: clearButton.left
                anchors.rightMargin: 6
                text: "Pop"
                onClicked: removeClicked()
        }

        Button {
                id: clearButton
                text: "Clear"
                height: 32
                width: 80
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                onClicked: clearClicked()
        }
}
