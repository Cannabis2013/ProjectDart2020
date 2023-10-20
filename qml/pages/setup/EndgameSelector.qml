import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "../../components/buttons"
import "../templates"

Rectangle {
        color: "transparent"

        property int selectedValue: 0

        GridLayout {
                anchors.fill: parent
                Text {
                        text: "Win condition:"
                        Layout.fillHeight: true
                        Layout.maximumWidth: 128
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                }

                Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        clip: true
                        color: "transparent"
                        Text {
                                id: selectedText
                                anchors.fill: parent
                                text: "Official"
                                color: "white"
                                verticalAlignment: Text.AlignVCenter
                        }
                        MouseArea {
                                anchors.fill: parent
                                onClicked: optionDialog.open()
                        }
                }
        }

        OptionsDialog {
                id: optionDialog
                onOptionClicked: (title, value) => {
                                         selectedText.text = title
                                         selectedValue = value
                                 }
        }
}
