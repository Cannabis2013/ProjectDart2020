import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"

Dialog {
        id: optionDialog
        clip: true
        visible: false
        modal: true

        width: 300
        height: 192

        horizontalPadding: 6
        verticalPadding: 0

        contentHeight: parent.height
        contentWidth: parent.width
        background: Rectangle {
                color: "transparent"
        }

        signal optionClicked(string title, int value)
        onOptionClicked: (title, value) => {
                                 optionOne.selected = optionOne.value === value
                                 optionTwo.selected = optionTwo.value === value
                         }

        GridLayout {
                anchors.fill: parent
                OptionBox {
                        id: optionOne
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        title: "Official"
                        description: "The first player to reach 0 with bulls or double as last throw wins"
                        value: 0
                        selected: true
                }

                OptionBox {
                        id: optionTwo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        title: "First overthrow"
                        description: "The first player to reach 0 or below wins the match."
                        value: 1
                }
        }
}
