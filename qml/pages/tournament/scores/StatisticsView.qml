import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "transparent"

        function updateValues(average, low, high) {
                averageText.text = average
                lowText.text = low
                highText.text = high
        }

        GridLayout {
                anchors.fill: parent
                columns: 3
                rows: 2
                rowSpacing: 0
                Text {
                        id: averageTitle
                        Layout.minimumHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Average"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: lowTitle
                        Layout.minimumHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Worst"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: highTitle
                        Layout.minimumHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        color: "white"
                        text: "Best"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: averageText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: lowText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: highText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                }
        }
}
