import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
        GridLayout {
                anchors.fill: parent
                Button {
                        flat: true
                        Layout.alignment: Qt.AlignHCenter
                        font.pointSize: 24
                        height: 48
                        text: "Menu"
                        onClicked: {
                                winnerModal.visible = false
                                menuRequest()
                        }
                }

                Button {
                        flat: true
                        Layout.alignment: Qt.AlignHCenter
                        font.pointSize: 24
                        height: 48
                        text: "Undo"
                        onClicked: {
                                winnerModal.visible = false
                                undoClicked()
                        }
                }

                Button {
                        flat: true
                        Layout.alignment: Qt.AlignHCenter
                        font.pointSize: 24
                        height: 48
                        text: "Restart"
                        onClicked: {
                                winnerModal.visible = false
                                restartClicked()
                        }
                }
        }
}
