function handleNumberPadClick(point) {
  const modId = getModId()
  enter(modId, point)
  unSelectMods()
}

function handleSpecialPadClick(point) {
  enter("S", point)
  unSelectMods()
}

function unSelectMods() {
  modTripple.selected = false
  modDouble.selected = false
}

function selectTrippeMod(modId) {
  modDouble.selected = false
}

function selectDoubleMod(modId) {
  modTripple.selected = false
}

function getModId() {
  if (modTripple.selected)
    return modTripple.text
  else if (modDouble.selected)
    return modDouble.text
  else
    return "S"
}
