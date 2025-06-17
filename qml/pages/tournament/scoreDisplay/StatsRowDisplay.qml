import QtQuick 6.0
import QtQuick.Layouts 1.3
import "statsScripts.js" as Scripts

Item {
  function setValues(statsInfo) {
    Scripts.setValues(statsInfo)
  }

  RowLayout {
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width
    height: parent.height
    spacing: 0

    Text {
      id: lowText
      font.pointSize: 12
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
      id: averageText
      font.pointSize: 12
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
      id: highText
      font.pointSize: 12
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
      font.pointSize: 12
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
