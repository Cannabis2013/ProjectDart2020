import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "compMessages.js" as Scripts

Item {
        function update() {
                Scripts.updateMessages()
        }

        CompMessage {
                id: finishRow
                anchors.left: parent.left
                anchors.top: parent.top
                height: 40
                width: 192
                imageUrl: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
                imageWidth: 27
                imageHeight: 20
        }

        CompMessage {
                id: scoreSpan
                anchors.top: parent.top
                anchors.right: parent.right
                height: 40
                width: 100
                imageWidth: 31
                imageHeight: 42
        }
}
