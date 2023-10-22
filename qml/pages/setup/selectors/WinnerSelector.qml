import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
        color: "transparent"

        property string configKey: "winCond"

        signal optionClicked(int value)
        onOptionClicked: value => {
                                 setSelectedValue(value)
                                 dartsConfig.setConfigData(configKey, value.toString())
                         }

        function setSelectedValue(value) {
                optionOne.selected = optionOne.value === value
                optionTwo.selected = optionTwo.value === value
                selectedValue = value
        }

        property int selectedValue: 0

        GridLayout {
                anchors.fill: parent
                rowSpacing: 12

                WinnerOption {
                        id: optionTwo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        title: "Beginner"
                        description: "The first player to reach 0 or below wins the match."
                        value: 1
                }

                WinnerOption {
                        id: optionOne
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        title: "Professional"
                        description: "The first player to reach 0 with bulls or double as last throw wins"
                        value: 0
                        selected: true
                }
        }

        Component.onCompleted: {
                const value = dartsConfig.readConfigData(configKey)
                if (value)
                        setSelectedValue(parseInt(value))
                else
                        setSelectedValue(0)
        }
}
