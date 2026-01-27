import QtQuick 6.0
import "../scripts/nameUtils.js" as Names

Rectangle {
  id: playerInfo

  signal openPlayerInfoDialog

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
    playerInfo.resetAnimation()
    scoreBox.text = "Score"
    inputsBox.text = "Inputs"
  }
  function resetAnimation() {
    backgroundAnimation.stop()
    playerInfo.color = "#1f1f1f"
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

  color: "#6f6f6f"

  ColorAnimation {
    id: backgroundAnimation
    from: "#1f1f1f"
    to: "#3f3f3f"
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
    anchors {top: parent.top;left: parent.left;right: parent.right;margins: 8}
    font.pixelSize: 40
    color: "white"
    horizontalAlignment: Text.AlignHCenter
  }
  Text {
    id: playerRemaining
    anchors {top: playerName.bottom;bottom: scoreBox.top;margins: 8}
    width: parent.width
    font.pixelSize: 0.5*height + 20
    font.weight: Font.Bold
    color: "white"
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }
  Text {
    id: scoreBox
    anchors {bottom: highText.top;left: parent.left; margins: 8}
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
    anchors {left: scoreBox.right;right: parent.right;bottom: roundText.top;margins: 8}
    height: 64
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "white"
    horizontalAlignment: Text.AlignHCenter
  }
  Text {
    id: lowText
    anchors {bottom: parent.bottom;right: averageText.left}
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
    anchors {bottom: parent.bottom; right: highText.left}
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
    anchors {bottom: parent.bottom;right: parent.horizontalCenter}
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
    anchors {bottom: parent.bottom;left: parent.horizontalCenter}
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
    anchors {bottom: parent.bottom;left:totalText.right}
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
    anchors {bottom: parent.bottom;left: turnIndex.right}
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
}
