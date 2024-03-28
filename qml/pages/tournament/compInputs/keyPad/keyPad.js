function handleNumberPadClick(point) {
        const modId = getModId()
        numberClicked(modId, point)
        unSelectMods()
}

function handleSpecialPadClick(point) {
        numberClicked("S", point)
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
