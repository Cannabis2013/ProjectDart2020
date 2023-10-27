import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
        color: "transparent"
        clip: true

        GridLayout {
                anchors.fill: parent

                Button {
                        Layout.alignment: Qt.AlignRight
                        width: 64
                        Layout.maximumHeight: 40
                        onClicked: menuRequest()
                        Text {
                                anchors.fill: parent
                                text: "back"
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignLeft
                        width: 64
                        Layout.maximumHeight: 40
                        onPressAndHold: restartClicked()
                        Text {
                                anchors.fill: parent
                                text: "Restart"
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                        }
                }
        }
}
