import QtQuick 6.0
import "../scripts/nameUtils.js" as Names
import "../scripts/infoDisplay.js" as Script

Rectangle {
  id: playerInfo

  signal openPlayerInfoDialog

  function subtract(value) {
    let score = parseInt(playerRemaining.text)
    const current = dartsScores.current()
    let result = current - value
    playerRemaining.text = result > 0 ? result : 0
  }
  function updateFinish(inputs) {
    const count = inputs.length;
    const turnIndex = count > 0 ? count : 0;

    let scoreSum = Script.sum(inputs)

    const remaining = dartsScores.current() - scoreSum;
    const row = dartsFinishes.finish(remaining, turnIndex);
    finishSuggestion.text = row.length > 0 ? `Finish with\n${row}` : "";
  }
  function resetAndUpdate() {
    const player = dartsPlayers.current()
    playerName.text = Names.shortenName(player, 9)

    playerRemaining.text = dartsScores.current()

    const stats = JSON.parse(dartsStats.current())
    lowText.text = `MIN\n${stats.low}`
    averageText.text = `MID\n${stats.average}`
    highText.text = `MAX\n${stats.high}`
    totalText.text = `HIT\n${stats.throwCount}`

    const indexes = JSON.parse(dartsTurns.indexes())
    turnIndex.text = `TRN\n${indexes.turnIndex + 1}`
    roundText.text = `RND\n${indexes.roundIndex}`

    playerInfo.resetAnimation()

    scoreBox.text = "Score"
    inputsBox.text = "Inputs"
  }

  function resetAnimation() {
    backgroundAnimation.stop()
    playerInfo.color = colors.bg
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

  color: colors.bg

  QtObject{
    id: colors
    readonly property color bg: "#2f2f2f"
    readonly property color bright: "#3f3f3f"
  }

  ColorAnimation {
    id: backgroundAnimation
    from: colors.bg
    to: colors.bright
    target: playerInfo
    property: "color"
    duration: 1500
    loops: ColorAnimation.Infinite
    easing.type: Easing.SineCurve
  }
  Text {
    id: playerName
    height: 40
    anchors {top: parent.top;left: parent.left;right: parent.right;margins: 8}
    font.pixelSize: 40
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    MouseArea {
      anchors.fill: parent
      onClicked: playerInfo.openPlayerInfoDialog()
    }
  }
  Text {
    id: playerRemaining
    anchors {top: playerName.bottom;bottom: scoreBox.top;margins: 8}
    width: parent.width
    font.pixelSize: 0.5*height + 20
    font.weight: Font.Bold
    color: "lightgray"
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }
  Text {
    id: inputsBox
    anchors {bottom: finishSuggestion.top;left: parent.left; margins: 8}
    height: 64
    width: parent.width / 2
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
  }
  Text {
    id: scoreBox
    anchors {right: parent.right;bottom: finishSuggestion.top;margins: 8}
    height: 64
    width: parent.width / 2
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
  }
  Text {
    id: finishSuggestion
    anchors {left: parent.left;bottom: lowText.top;margins: 8}
    height: 80
    width: parent.width
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: lowText
    anchors {bottom: parent.bottom;right: averageText.left}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: averageText
    anchors {bottom: parent.bottom; right: highText.left}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: highText
    anchors {bottom: parent.bottom;right: parent.horizontalCenter}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text {
    id: totalText
    anchors {bottom: parent.bottom;left: parent.horizontalCenter}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text{
    id: turnIndex
    anchors {bottom: parent.bottom;left:totalText.right}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text{
    id: roundText
    anchors {bottom: parent.bottom;left: turnIndex.right}
    width: 64
    height: 56
    lineHeight: 28
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 24
    font.weight: Font.Bold
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
}
