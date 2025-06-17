.import "nameUtils.js" as Names

function updatePreview(inputs) {
  const current = dartsScores.current()
  let sum = 0
  let input = {}
  for (var i = 0; i < inputs.length; i++) {
    input = inputs[i]
    sum += toScore(input)
  }
  playerScore.text = sum < current ? current - sum : 0
}

function toScore(input) {
  const mod = input.modId
  const point = input.point
  const mult = mod === "T" ? 3 : mod === "D" ? 2 : 1
  return point * mult
}

function updateValues() {
  const player = JSON.parse(dartsPlayers.currentPlayer())
  const score = dartsScores.current()
  const stats = JSON.parse(dartsStats.report())
  playerName.text = Names.shortenName(player.name, 9)
  playerScore.text = score
  statsDisplay.setValues(stats)
}
