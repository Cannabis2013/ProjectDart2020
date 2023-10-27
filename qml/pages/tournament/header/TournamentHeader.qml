import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
        color: "transparent"
        clip: true

        GridLayout {
                anchors.fill: parent

                Button {
                        flat: true
                        font.pointSize: 20
                        Layout.minimumWidth: 64
                        Layout.maximumHeight: 40
                        onClicked: menuRequest()
                        text: "back"
                }

                Button {
                        flat: true
                        font.pointSize: 20
                        Layout.minimumWidth: 64
                        Layout.maximumHeight: 40
                        onClicked: restartClicked()
                        text: "Restart"
                }

                Rectangle {
                        Layout.fillWidth: true
                }
        }
}
