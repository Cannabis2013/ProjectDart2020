function handleNumberPadClicked(point) {
        const modId = getSelectedId()
        unSelectAll()
        inputsDisplay.addInput(modId, point)
}

function report() {
        const inputs = inputsDisplay.readInputs()
        reportScores(inputs)
        inputsDisplay.flushInputs()
}

function handleSpecialPadClicked(value) {
        unSelectAll()
        inputsDisplay.addInput("S", value)
}

function handleModPadClicked(modId) {
        const mods = modKeys.modObjects
        for (var i = 0; i < mods.length; i++) {
                const mod = mods[i]
                if (mod.modId !== modId)
                        mod.select(false)
        }
}

function unSelectAll() {
        const modObjects = modKeys.modObjects
        for (var i = 0; i < modObjects.length; i++) {
                const mod = modObjects[i]
                mod.select(false)
        }
}

function getSelectedId() {
        const modObjects = modKeys.modObjects
        for (var i = 0; i < modObjects.length; i++) {
                const modObject = modObjects[i]
                if (modObject.selected)
                        return modObject.modId
        }
        return "S"
}
