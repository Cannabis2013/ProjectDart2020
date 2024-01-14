import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerStatistics.js" as Scripts

Item {
        id: playerStatistics

        property int average: 0
        onAverageChanged: averageText.text = average

        property int low: 0
        onLowChanged: lowText.text = low

        property int high: 0
        onHighChanged: highText.text = high

        property int throwCount: 0
        onThrowCountChanged: totalText.text = throwCount

        GridLayout {
                anchors.fill: parent
                columns: 4
                rowSpacing: 0
                Text {
                        id: averageTitle
                        Layout.preferredHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 12
                        font.weight: Font.Bold
                        color: "white"
                        text: "Average"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: lowTitle
                        Layout.preferredHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 12
                        font.weight: Font.Bold
                        color: "white"
                        text: "Worst"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: highTitle
                        Layout.preferredHeight: 48
                        Layout.fillWidth: true
                        font.pointSize: 12
                        font.weight: Font.Bold
                        color: "white"
                        text: "Best"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                }

                Text {
                        id: totalTitle
                        Layout.preferredHeight: 48
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                        text: "Total"
                }

                Text {
                        id: averageText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        text: playerStatistics.average
                }

                Text {
                        id: lowText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        text: playerStatistics.low
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
                        text: playerStatistics.high
                }

                Text {
                        id: totalText
                        Layout.maximumHeight: 16
                        font.pointSize: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                        text: playerStatistics.throwCount
                }
        }
}
