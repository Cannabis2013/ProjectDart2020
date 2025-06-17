import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0
import "scoreScripts.js" as Scripts

Rectangle {
  id: playerInfoRect
  clip: true
  color: "green"

  function update() {
    Scripts.updateValues()
  }

  function updateScorePreview(inputs) {
    Scripts.updatePreview(inputs)
  }

  QtObject {
    id: playerInfo
    property string fullName: ""
    property string formattedName: ""
  }

  Text {
    id: playerName
    anchors.top: parent.top
    width: parent.width
    height: 36
    font.pointSize: 20
    color: "white"
    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerScore
    anchors.top: playerName.bottom
    width: parent.width
    font.pixelSize: 52
    font.weight: Font.Bold
    color: "white"
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }

  StatsRowDisplay {
    id: statsDisplay
    anchors.left: parent.left
    anchors.leftMargin: 4
    anchors.right: parent.right
    anchors.rightMargin: 4
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 4
    height: 28
  }

  MouseArea {
    anchors.fill: parent
    onPressed: Scripts.openInputsDialog()
  }
}
