.import "infoDialog.js" as InputDialog

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
  playerInfo.fullName = player.name
  playerInfo.formattedName = shortenName(player.name, 9)
  playerName.text = playerInfo.formattedName
  playerScore.text = score
  statsDisplay.setValues(stats)
}

function shortenName(name, limit) {
  if (name.length < limit)
    return name
  const found = name.match(/\s[A-z]*/g)
  const formatted = formatName(name, found, limit)
  if (formatted.length > limit)
    return shortenName(formatted)
  return formatted
}

function formatName(name, found, limit) {
  if (found.lenth <= 0)
    return name.substring(0, limit) + ".." // Ex.: Johnny Walke..
  else if (found.length === 1)
    return reduceLastName(name) // Has only  a lastname
  else if (found.length > 1)
    return reduceMiddleNames(name) // Has middlename(s)
  else
    return name
}

function reduceLastName(name) {
  const index = name.indexOf(" ")
  return name.substring(0, index + 2) + "."
}

function reduceMiddleNames(name) {
  const firstIndex = name.indexOf(" ")
  const lastIndex = name.lastIndexOf(" ")
  const firstName = name.substring(0, firstIndex)
  const lastName = name.substring(lastIndex, name.length)
  return firstName + lastName
}

function openInputsDialog() {
  const name = playerInfo.fullName
  InputDialog.open(name)
}
