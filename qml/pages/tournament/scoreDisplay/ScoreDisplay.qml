import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0
import "scoreScripts.js" as Scripts
import "inputsScripts.js" as InputsModal

Rectangle {
  id: playerInfoRect
  clip: true
  color: Qt.rgba(63, 63, 63, 0.1)

  function update() {
    Scripts.updateValues()
  }

  function updateScorePreview(inputs) {
    Scripts.updatePreview(inputs)
  }

  Text {
    id: playerName
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: inputsButton.left
    height: 36
    font.pointSize: 20
    color: "white"
    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerScore
    anchors.top: playerName.bottom
    anchors.left: parent.left
    anchors.right: inputsButton.left
    font.pixelSize: 58
    font.weight: Font.Bold
    color: "white"
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }

  StatsRowDisplay {
    id: statsDisplay
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: playerScore.horizontalCenter
    height: 28
    width: 160
  }

  Button {
    id: inputsButton
    onClicked: InputsModal.open()
    height: 40
    width: 90
    anchors.right: parent.right
    anchors.rightMargin: 8
    anchors.top: parent.top
    anchors.topMargin: 8
    text: "Inputs"
  }
}
