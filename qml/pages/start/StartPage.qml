import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../templates"

Page {
        id: startPageContentBody

        signal requestTournamentPage
        signal requestAboutPage
        signal quickGameClicked
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
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
                        text: "1v1"
                        onClicked: quickGameClicked()
                        opacity: 1
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
                        text: "Practice"
                        onClicked: {
                                dartsController.init(["I"], 0)
                                requestTournamentPage()
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
                        text: "Start game"
                        onClicked: {
                                setupGameClicked()
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
                        text: "Resume from last game"
                        onClicked: {
                                dartsController.initFromSaved()
                                requestTournamentPage()
                        }
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
                        text: "About"
                        onClicked: requestAboutPage()
                }

                Button {
                        Layout.alignment: Qt.AlignHCenter
                        width: 192
                        Layout.maximumHeight: 32
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
