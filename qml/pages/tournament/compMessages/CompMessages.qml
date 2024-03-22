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
                height: parent.height
                width: 192
                imageUrl: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
                imageWidth: 27
                imageHeight: 20
        }

        CompMessage {
                id: scoreSpan
                anchors.right: parent.right
                imageUrl: "qrc:/pictures/Ressources/Pictures/span.png"
                height: parent.height
                width: 100
                imageWidth: 42
                imageHeight: 20
        }
}
