import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Rectangle {
  id: winnerModal

  anchors.fill: parent
  color: "black"

  signal restartClicked
  signal undoClicked

  MouseArea {
    anchors.fill: parent
  }

  MouseArea {
    anchors.fill: parent
  }

  GridLayout {
    flow: GridLayout.TopToBottom
    anchors.centerIn: parent
    width: parent.width - 12
    height: parent.height

    Item {
      Layout.fillHeight: true
      Layout.fillWidth: true
      Text {
        id: winnerText
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 12
        font.pointSize: 32
        font.weight: Font.Medium
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        wrapMode: Text.WordWrap
      }

      AnimatedImage {
        id: animatedImage
        width: parent.width
        anchors.top: winnerText.bottom
        anchors.topMargin: 12
        anchors.bottom: parent.bottom
      }

      Component.onCompleted: {
        const turnReport = JSON.parse(dartsPlayers.winnerInfo())
        winnerText.text = turnReport.winnerName
        animatedImage.source = turnReport.winnerImage
      }
    }

    DialogButtons {
      Layout.fillWidth: true
      Layout.preferredHeight: 48
    }
  }
}
