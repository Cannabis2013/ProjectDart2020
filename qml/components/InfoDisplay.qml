import QtQuick 6.0

import "../utils/nameUtils.js" as Names

Rectangle {
  id: playerInfo

  function resetAnimation() {
    backgroundAnimation.stop()
    playerInfo.color = Qt.rgba(63, 63, 63, .1)
  }

  function resetAndUpdate() {
    const player = dartsPlayers.current()
    const stats = JSON.parse(dartsStats.current())
    const indexes = JSON.parse(dartsTurns.indexes())


    playerName.text = Names.shortenName(player, 9)
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

    target: playerInfo
    property: "color"

    duration: 1500
    loops: ColorAnimation.Infinite

    easing.type: Easing.SineCurve
  }

  MouseArea {
    anchors.fill: parent

    onClicked: playerInfo.openPlayerInfoDialog()
  }

  Text {
    id: playerName

    height: 40

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 6

    font.pixelSize: 40
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: playerRemaining

    anchors.top: playerName.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 8

    height: 90

    font.pixelSize: 90
    font.weight: Font.Bold
    color: "white"

    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }

  Text {
    id: lowText

    anchors.bottom: parent.bottom
    anchors.right: averageText.left

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: averageText

    anchors.bottom: parent.bottom
    anchors.right: highText.left

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: highText

    anchors.bottom: parent.bottom
    anchors.right: parent.horizontalCenter

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: totalText

    anchors.bottom: parent.bottom
    anchors.left: parent.horizontalCenter

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text{
    id: turnIndex

    anchors.bottom: parent.bottom
    anchors.left: totalText.right

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold

    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text{
    id: roundText

    anchors.bottom: parent.bottom
    anchors.left: turnIndex.right

    width: 64
    height: 48

    lineHeight: 24
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 16
    font.weight: Font.Bold

    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: scoreBox

    anchors.bottom: highText.top
    anchors.left: parent.left
    anchors.margins: 8

    height: 64
    width: 128

    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }

  Text {
    id: inputsBox

    anchors.left: scoreBox.right
    anchors.right: parent.right
    anchors.bottom: roundText.top
    anchors.margins: 8

    height: 64

    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "white"

    horizontalAlignment: Text.AlignHCenter
  }
}
