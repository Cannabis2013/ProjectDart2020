import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        id: messageItem

        property url imageUrl: ""
        onImageUrlChanged: messageIcon.source = imageUrl

        property string message: ""
        onMessageChanged: textContent.text = message

        property int imageHeight: 34
        onImageHeightChanged: messageIcon.Layout.preferredHeight = imageHeight
        property int imageWidth: 40
        onImageWidthChanged: messageIcon.Layout.preferredWidth = imageWidth

        function setValues(message, iconUrl) {
                textContent.text = message
                messageIcon.source = iconUrl
        }

        onVisibleChanged: {
                if (visible)
                        opacityEffect.start()
        }

        NumberAnimation on opacity {
                id: opacityEffect
                from: 0
                to: 1
                duration: 350
        }

        RowLayout {
                id: layout
                anchors.fill: parent
                spacing: 6
                Image {
                        id: messageIcon
                        Layout.preferredHeight: messageItem.imageHeight
                        Layout.preferredWidth: messageItem.imageWidth
                }

                Text {
                        id: textContent
                        font.pointSize: 28
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: messageItem.message
                }
        }
}
