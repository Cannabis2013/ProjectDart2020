import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Page {
        id: startPageContentBody

        signal requestTournamentPage

        signal quickGameClicked
        signal setupGameClicked
        signal manageContentClicked
        signal settingsButtonClicked

        property color labelBackgroundColor: "black"
        onLabelBackgroundColorChanged: {
                titleEdit.labelBackgroundColor = labelBackgroundColor
                legsEdit.labelBackgroundColor = labelBackgroundColor
                maxPlayerEdit.labelBackgroundColor = labelBackgroundColor
        }

        StartPageBackDrop {
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

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "1v1"
                        onClicked: {
                                dartsController.init(["I", "II"])
                                requestTournamentPage()
                        }
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Practice"
                        onClicked: {
                                dartsController.init(["I"])
                                requestTournamentPage()
                        }
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Start game"
                        onClicked: {
                                setupGameClicked()
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
