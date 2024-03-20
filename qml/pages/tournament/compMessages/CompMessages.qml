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
                anchors.left: parent.left
                anchors.leftMargin: 6
                spacing: 6
                move: Transition {
                        NumberAnimation {
                                properties: "x,y"
                                duration: 250
                        }
                }
        }
}
