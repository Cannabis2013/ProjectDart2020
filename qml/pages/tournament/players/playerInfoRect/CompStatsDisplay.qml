import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compStatsDisplay.js" as Scripts

Item {
        function setValues(statsInfo) {
                Scripts.setValues(statsInfo)
        }

        GridLayout {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 24
                rowSpacing: 0

                Text {
                        id: averageText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        lineHeight: 12
                        lineHeightMode: Text.FixedHeight
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Average"
                }

                Text {
                        id: lowText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        lineHeight: 12
                        lineHeightMode: Text.FixedHeight
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Low"
                }

                Text {
                        id: highText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        lineHeight: 12
                        lineHeightMode: Text.FixedHeight
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "high"
                }

                Text {
                        id: totalText
                        font.pointSize: 12
                        Layout.fillHeight: true
                        lineHeightMode: Text.FixedHeight
                        lineHeight: 12
                        Layout.fillWidth: true
                        font.weight: Font.Bold
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Total"
                }
        }
}
