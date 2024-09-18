import QtQuick 6.0
import QtQuick.Layouts 1.3
import "compStatsDisplay.js" as Scripts

Item {
    function setValues(statsInfo) {
        Scripts.setValues(statsInfo)
    }

    GridLayout {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 28
        rowSpacing: 0
        Text {
            id: averageText
            font.pointSize: 10
            Layout.fillHeight: true
            lineHeight: 14
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
            font.pointSize: 10
            Layout.fillHeight: true
            lineHeight: 14
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
            font.pointSize: 10
            Layout.fillHeight: true
            lineHeight: 14
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
            font.pointSize: 10
            Layout.fillHeight: true
            lineHeightMode: Text.FixedHeight
            lineHeight: 14
            Layout.fillWidth: true
            font.weight: Font.Bold
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: "Total"
        }
    }
}
