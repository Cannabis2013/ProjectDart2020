import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"

Dialog {
        id: optionDialog
        modal: true
        width: 300
        height: 250
        anchors.centerIn: parent
        horizontalPadding: 12

        background: Rectangle {
                color: "black"
                radius: 12
        }

        Timer {
                id: closeTimer
                interval: 300
                running: false
                onTriggered: optionDialog.close()
        }

        signal optionClicked(string title, int value)
        onOptionClicked: (title, value) => {
                                 optionOne.selected = optionOne.value === value
                                 optionTwo.selected = optionTwo.value === value
                                 closeTimer.start()
                         }

        GridLayout {
                columns: 2
                anchors.fill: parent
                rowSpacing: 12

                Text {
                        Layout.columnSpan: 2
                        height: 32
                        Layout.fillWidth: true
                        text: "Select winner condition"
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 24
                        font.weight: Font.Bold
                        color: "white"
                }

                OptionBox {
                        id: optionOne
                        Layout.fillWidth: true
                        height: 160
                        title: "Official"
                        description: "The first player to reach 0 with bulls or double as last throw wins"
                        value: 0
                        selected: true
                }

                OptionBox {
                        id: optionTwo
                        Layout.fillWidth: true
                        height: 160
                        title: "First overthrow"
                        description: "The first player to reach 0 or below wins the match."
                        value: 1
                }

                Rectangle {
                        Layout.fillHeight: true
                }
        }
}
