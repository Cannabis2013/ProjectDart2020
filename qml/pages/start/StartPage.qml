import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../templates"

Page {
        id: startPageContentBody

        signal requestTournamentPage
        signal requestAboutPage
        signal setupGameClicked

        Anti1964BackDrop {
                anchors.fill: parent
        }

        GridLayout {
                id: gridLayout
                anchors.fill: parent
                rowSpacing: 5
                flow: GridLayout.TopToBottom

                Rectangle {
                        height: 192
                        color: "transparent"
                }

                Button {
                        flat: true
                        font.pointSize: 24
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumWidth: 192
                        Layout.maximumWidth: 192
                        Layout.maximumHeight: 48
                        text: "Classic 1v1"
                        onClicked: setupGameClicked()
                        opacity: 1
                }

                Button {
                        flat: true
                        font.pointSize: 24
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumWidth: 192
                        Layout.maximumWidth: 192
                        Layout.maximumHeight: 48
                        text: "Practice"
                        onClicked: {
                                dartsController.init(["I"], 0, 501)
                                requestTournamentPage()
                        }
                }

                Button {
                        flat: true
                        font.pointSize: 24
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumWidth: 192
                        Layout.maximumWidth: 192
                        Layout.maximumHeight: 48
                        text: "Resume game"
                        onClicked: {
                                dartsController.initFromSaved()
                                requestTournamentPage()
                        }
                }

                Button {
                        flat: true
                        font.pointSize: 24
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumWidth: 192
                        Layout.maximumWidth: 192
                        Layout.maximumHeight: 48
                        text: "About"
                        onClicked: requestAboutPage()
                }

                Button {
                        flat: true
                        font.pointSize: 24
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumWidth: 192
                        Layout.maximumWidth: 192
                        Layout.maximumHeight: 48
                        text: "Quit"
                        onClicked: Qt.quit()
                }

                Rectangle {
                        id: emptyRect
                        Layout.fillHeight: true
                        border.width: 1
                }
        }
}
