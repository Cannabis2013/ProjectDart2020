import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0
import "scoreScripts.js" as Scripts

Rectangle {
  id: playerInfoRect

  clip: true

  color: Qt.rgba(63, 63, 63, 0.1)

  signal openPlayerInfoDialog

  function resetAndUpdate() {
    Scripts.updateValues()
  }

  function updateScores(inputs, inputsScore) {
    Scripts.updateScores(inputs, inputsScore)
  }

  function subtract(value) {
    Scripts.subtractValue(value)
  }

  ColorAnimation {
    id: backgroundAnimation

    from: Qt.rgba(63, 63, 63, 0.1)
    to: Qt.rgba(63, 63, 63, 0.2)

    target: playerInfoRect
    property: "color"

    duration: 1000
    loops: ColorAnimation.Infinite

    easing.type: Easing.SineCurve
  }

  QtObject {
    id: scoreInfo
    property int currentScore: 0
  }

  MouseArea{
    anchors.fill: parent

    onClicked: openPlayerInfoDialog()
  }

  Text {
    id: playerName
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: scoreBox.left
    anchors.margins: 6
    height: 36
    font.pointSize: 20
    color: "white"
    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerScore
    anchors.top: playerName.bottom
    anchors.left: parent.left
    anchors.right: scoreBox.left
    anchors.bottom: statsDisplay.top
    anchors.margins: 6
    font.pixelSize: 48
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

  TextBox {
    id: scoreBox
    label: "SCORE"
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.bottom: parent.verticalCenter
    anchors.margins: 6
    width: 160
    fontSize: 20
  }

  TextBox {
    id: inputsBox
    label: "INPUTS"
    anchors.right: parent.right
    anchors.top: parent.verticalCenter
    anchors.bottom: parent.bottom
    anchors.margins: 6
    width: 160
    fontSize: 20
  }
}
