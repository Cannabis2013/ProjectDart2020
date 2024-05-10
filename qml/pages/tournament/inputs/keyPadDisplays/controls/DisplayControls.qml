import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "displayControls.js" as Scripts

Item {
        Button {
                id: removeButton
                width: 70
                height: 30
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: clearButton.left
                anchors.rightMargin: 6
                text: "Pop"
                onClicked: Scripts.removeOne()
        }

        Button {
                id: clearButton
                text: "Flush"
                width: 80
                height: 30
                font.pixelSize: 12
                anchors.right: parent.right
                onClicked: Scripts.clearInputs()
        }
}
