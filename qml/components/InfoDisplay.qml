import QtQuick 6.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 6.0

import "../utils/nameUtils.js" as Names

Rectangle {
  id: playerInfoRect

  function resetAnimation() {
    backgroundAnimation.stop()
    playerInfoRect.color = Qt.rgba(63, 63, 63, .1)
  }

  function resetAndUpdate() {
    const player = JSON.parse(dartsPlayers.current())
    const stats = JSON.parse(dartsStats.current())
    const indexes = JSON.parse(dartsTurns.report())


    playerName.text = Names.shortenName(player.name, 9)
    playerRemaining.text = dartsScores.current()

    averageText.text = `MID\n${stats.average}`
    lowText.text = `MIN\n${stats.low}`
    highText.text = `MAX\n${stats.high}`
    totalText.text = `HIT\n${stats.throwCount}`
    turnIndex.text = `TRN\n${indexes.turnIndex + 1}`
    roundText.text = `RND\n${indexes.roundIndex}`

    resetAnimation()

    scoreBox.text = "Score"
    inputsBox.text = "Inputs"
  }

  function updateScores(inputs, inputsScore) {
    let text = ""

    inputs.forEach(input => text += `${input.modId}${input.point} `)

    scoreBox.text = inputs.length > 0 ? `Score\n${inputsScore}` : "Score"
    inputsBox.text = inputs.length > 0 ? `Inputs\n${text}` : "Inputs"

    if (inputs.length > 0)
      backgroundAnimation.start()
    else
      resetAnimation()
  }

  function subtract(value) {
    let score = parseInt(playerRemaining.text)
    const current = dartsScores.current()
    let result = current - value
    playerRemaining.text = result > 0 ? result : 0
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

  MouseArea {
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

    font.pixelSize: 24
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerRemaining

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
    anchors.right: averageText.left

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: averageText

    anchors.bottom: parent.bottom
    anchors.right: highText.left

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: highText

    anchors.bottom: parent.bottom
    anchors.right: parent.horizontalCenter

    height: 32
    width: 64

    lineHeight: 14
    lineHeightMode: Text.FixedHeight

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: totalText

    anchors.bottom: parent.bottom
    anchors.left: parent.horizontalCenter

    height: 32
    width: 64

    lineHeightMode: Text.FixedHeight
    lineHeight: 14

    font.pointSize: 12
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text{
    id: turnIndex

    anchors.bottom: parent.bottom
    anchors.left: totalText.right

    lineHeightMode: Text.FixedHeight
    lineHeight: 14

    height: 32
    width: 64

    color: "white"

    font.pointSize: 12
    font.weight: Font.Bold

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text{
    id: roundText

    anchors.bottom: parent.bottom
    anchors.left: turnIndex.right

    lineHeightMode: Text.FixedHeight
    lineHeight: 14

    height: 32
    width: 64

    color: "white"

    font.pointSize: 12
    font.weight: Font.Bold

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: scoreBox

    anchors.top: parent.top
    anchors.right: parent.right
    anchors.bottom: inputsBox.top
    anchors.margins: 6

    height: 52
    width: 128

    font.pixelSize: 20
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: inputsBox

    anchors.right: parent.right
    anchors.bottom: roundText.top
    anchors.margins: 6

    height: 52
    width: 128

    font.pixelSize: 20
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }
}
