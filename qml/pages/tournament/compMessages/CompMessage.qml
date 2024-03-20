import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        id: messageItem

        height: 74
        width: 128
        opacity: 0

        function setValues(message, iconUrl) {
                textContent.text = message
                messageIcon.source = iconUrl
        }

        NumberAnimation on opacity {
                from: 0
                to: 1
                duration: 500
        }

        Image {
                id: messageIcon
                anchors.verticalCenter: parent.verticalCenter
                width: 34
                height: 34
        }

        Rectangle {
                id: textRect
                color: "blue"
                x: 24
                y: 40
                height: 22
                radius: 6

                Text {
                        id: textContent
                        anchors.centerIn: parent
                        onWidthChanged: textRect.width = width + 12
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                }
        }
}
