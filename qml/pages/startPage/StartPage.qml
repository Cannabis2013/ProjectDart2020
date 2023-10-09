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
        Rectangle {
                id: backgroundRect
                anchors.fill: parent
                color: "black"
        }

        Image {
                id: fckImage
                source: "qrc:/pictures/Ressources/fck.png"

                x: parent.width / 2 - width / 2
                y: 5

                width: 150
                height: 150
        }
        Image {
                id: dartLogo
                source: "qrc:/pictures/Ressources/pngfuel.com.png"

                x: parent.width / 2 - 175
                y: 5

                width: 130
                height: 130
        }
        Image {
                id: tuborgImage

                source: "qrc:/pictures/Ressources/tuborgclassic.png"

                x: parent.width / 2 + 25
                y: 25

                width: 130
                height: 130

                rotation: 25
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
                        text: "QUICK: 1v1"
                        onClicked: {
                                dartsController.init(["I", "II"])
                                requestTournamentPage()
                        }
                }

                StartMenuButton {
                        Layout.alignment: Qt.AlignHCenter
                        text: "QUICK: Practice"
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
