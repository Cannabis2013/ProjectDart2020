.import "../../../utils/nameUtils.js" as Names

function updateValues() {
  const player = JSON.parse(dartsPlayers.current())
  const score = dartsScores.current()
  const stats = JSON.parse(dartsStats.report())
  playerName.text = Names.shortenName(player.name, 9)
  playerScore.text = score
  statsDisplay.setValues(stats)
}
