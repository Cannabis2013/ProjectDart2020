import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0

import "../../utils/nameUtils.js" as Names

Rectangle {
  id: playerInfoRect

  function resetAnimation(){
    backgroundAnimation.stop()
    playerInfoRect.color = Qt.rgba(63,63,63,.1)
  }

  function resetAndUpdate() {
    const player = JSON.parse(dartsPlayers.current())
    const stats = JSON.parse(dartsStats.current())

    playerName.text = Names.shortenName(player.name, 9)
    playerScore.text = dartsScores.current()

    averageText.text = `MID\n${stats.average}`
    lowText.text = `MIN\n${stats.low}`
    highText.text = `MAX\n${stats.high}`
    totalText.text = `HIT\n${stats.throwCount}`

    resetAnimation()

    scoreBox.text = ""
    inputsBox.text = ""
  }

  function updateScores(inputs, inputsScore) {
    let text = ""

    inputs.forEach(input => text += `${input.modId}${input.point} `)

    inputsBox.text = `Inputs\n${text}`
    scoreBox.text = `Score\n${inputsScore}`

    if(inputs.length > 0)
      backgroundAnimation.start()
    else
      resetAnimation()
  }

  function subtract(value) {
    let score = parseInt(playerScore.text)
    const current = dartsScores.current()
    let result = current - value
    playerScore.text = result > 0 ? result : 0
  }

  color: Qt.rgba(63, 63, 63, 0.1)

  signal openPlayerInfoDialog

  ColorAnimation {
    id: backgroundAnimation

    from: Qt.rgba(63, 63, 63, 0.1)
    to: Qt.rgba(63, 63, 63, 0.2)

    target: playerInfoRect
    property: "color"

    duration: 1500
    loops: ColorAnimation.Infinite

    easing.type: Easing.SineCurve
  }

  MouseArea{
    anchors.fill: parent

    onClicked: openPlayerInfoDialog()
  }

  Text {
    id: playerName

    height: 36

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: scoreBox.left
    anchors.margins: 6

    font.pointSize: 20
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerScore

    anchors.top: playerName.bottom
    anchors.left: parent.left
    anchors.right: scoreBox.left
    anchors.bottom: lowText.top
    anchors.margins: 6

    font.pixelSize: 48
    font.weight: Font.Bold
    color: "white"

    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }

  Text {
    id: lowText

    anchors.bottom: parent.bottom

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    text: "Low"
  }

  Text {
    id: averageText

    anchors.bottom: parent.bottom
    anchors.left: lowText.right

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    text: "Average"
  }

  Text {
    id: highText

    anchors.bottom: parent.bottom
    anchors.left: averageText.right

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    text: "high"
  }

  Text {
    id: totalText

    anchors.bottom: parent.bottom
    anchors.left: highText.right

    height: 32
    width: 64

    lineHeightMode: Text.FixedHeight
    lineHeight: 14

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    text: "Total"
  }

  Text {
    id: scoreBox

    anchors.top: parent.top
    anchors.right: parent.right
    anchors.bottom: parent.verticalCenter
    anchors.margins: 6

    width: 160

    font.pixelSize: 16
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: inputsBox

    anchors.right: parent.right
    anchors.top: parent.verticalCenter
    anchors.bottom: parent.bottom
    anchors.margins: 6

    width: 160

    font.pixelSize: 16
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }
}
