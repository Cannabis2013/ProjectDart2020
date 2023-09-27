function inputModeFromString() {
        var inputString = inputModeSelector.currentValue
        var inputCode = convertInputStringToHex(inputString)
        return inputCode
}

function convertInputStringToHex(inputMode) {
        var inputModes = stringModels.inputModes
        if (inputMode === inputModes[0])
                return TournamentContext.pointMode
        else if (inputMode === inputModes[1])
                return TournamentContext.scoreMode
}

function initializeComponents() {
        keyPointSelector.currentIndex = defaultStateValues.defaultKeyPointIndex
        inputModeSelector.currentIndex = defaultStateValues.defaultInputModeIndex
}
