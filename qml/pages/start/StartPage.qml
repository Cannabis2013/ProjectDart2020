import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../templates"

BlackPage {
        id: startPageContentBody

        signal requestTournamentPage
        signal requestAboutPage
        signal quickGameClicked
        signal setupGameClicked

        property color labelBackgroundColor: "black"
        onLabelBackgroundColorChanged: {
                titleEdit.labelBackgroundColor = labelBackgroundColor
                legsEdit.labelBackgroundColor = labelBackgroundColor
                maxPlayerEdit.labelBackgroundColor = labelBackgroundColor
        }

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

                GridLayout {
                        Layout.maximumWidth: 256
                        Layout.maximumHeight: 64
                        columnSpacing: 6
                        Layout.alignment: Qt.AlignHCenter
                        StartMenuButton {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: "1v1"
                                onClicked: quickGameClicked()
                        }

                        StartMenuButton {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: "Practice"
                                onClicked: {
                                        dartsController.init(["I"])
                                        requestTournamentPage()
                                }
                        }

                        StartMenuButton {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: "Start game"
                                onClicked: {
                                        setupGameClicked()
                                }
                        }
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Resume from last game"
                        onClicked: {
                                dartsController.initFromSaved()
                                requestTournamentPage()
                        }
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "About"
                        onClicked: requestAboutPage()
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
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
