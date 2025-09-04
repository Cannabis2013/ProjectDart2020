.import "../../../utils/nameUtils.js" as Names

function updateValues() {
  const player = JSON.parse(dartsPlayers.current())
  scoreInfo.currentScore = dartsScores.current()
  const stats = JSON.parse(dartsStats.current())
  playerName.text = Names.shortenName(player.name, 9)
  playerScore.text = scoreInfo.currentScore
  statsDisplay.setValues(stats)

  backgroundAnimation.stop()
  playerInfoRect.color = Qt.rgba(63,63,63,.1)

  scoreBox.value = 0
}

function updateScores(inputs, inputsScore) {
  let text = ""

  inputs.forEach(input => text += `${input.modId}${input.point} `)

  inputsBox.value = text
  scoreBox.value = inputsScore

  if(inputs.length > 0)
    backgroundAnimation.start()
  else{
    backgroundAnimation.stop()
    playerInfoRect.color = Qt.rgba(63,63,63,.1)
  }
}

function subtractValue(value) {
  let score = parseInt(playerScore.text)
  let result = scoreInfo.currentScore - value
  playerScore.text = result > 0 ? result : 0
}
