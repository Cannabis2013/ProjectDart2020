import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "compMessages.js" as Scripts

Item {
        function update() {
                Scripts.updateMessages()
        }

        Row {
                id: messageContainer
                anchors.fill: parent
                anchors.leftMargin: 6
                spacing: 24
                move: Transition {
                        NumberAnimation {
                                properties: "x"
                                duration: 250
                        }
                }

                CompMessage {
                        id: finishRow
                        height: parent.height
                        width: 128
                        imageUrl: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
                        imageWidth: 40
                        imageHeight: 34
                }

                CompMessage {
                        id: scoreSpan
                        imageUrl: "qrc:/pictures/Ressources/Pictures/span.png"
                        height: parent.height
                        width: 96
                        imageWidth: 40
                        imageHeight: 34
                }
        }
}
