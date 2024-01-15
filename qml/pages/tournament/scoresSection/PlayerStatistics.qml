import QtQuick 2.15
import QtQuick.Layouts 1.3
import "playerStatistics.js" as Scripts

Item {
        function updateStatistics(statistics) {
                Scripts.updateValues(statistics)
        }

        GridLayout {
                anchors.fill: parent
                rowSpacing: 0

                Text {
                        id: averageText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        text: "Average"
                }

                Text {
                        id: lowText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        text: "Low"
                }

                Text {
                        id: highText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        text: "high"
                }

                Text {
                        id: totalText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        text: "Total"
                }
        }
}
