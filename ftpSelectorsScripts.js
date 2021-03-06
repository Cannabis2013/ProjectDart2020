function convertKeyModifierToHex(key){
    var keyIdentifiers = stringModels.keyIdentifiers;
    if(key === keyIdentifiers[0])
        return 0x2A;
    else if(key === keyIdentifiers[1])
        return 0x2B;
    else if(key === keyIdentifiers[2])
        return 0x2C;
    else
        return -1;
}
function convertHintToHex(hint){
    var hints = stringModels.displayHints;
    if(hint === hints[0])
        return DataModelContext.singleAttempt;
    else if(hint === hints[1])
        return DataModelContext.multiAttempt;
    else
        return -1;
}

function convertInputStringToHex(inputMode)
{
    var inputModes = stringModels.inputModes;
    if(inputMode === inputModes[0])
        return TournamentContext.pointMode;
    else if(inputMode === inputModes[1])
        return TournamentContext.scoreMode;
}

function conditionKeyCode()
{
    var keyString = winConditionSelector.currentValue;
    var keyCode = convertKeyModifierToHex(keyString);
    return keyCode;
}

function tableViewHintFromString()
{
    var hintString = displayHintSelector.currentValue;
    var hintCode = convertHintToHex(hintString);
    return hintCode;
}

function inputModeFromString()
{
    var inputString = inputModeSelector.currentValue;
    var inputCode = convertInputStringToHex(inputString);
    return inputCode;
}

function initializeComponents(){
    keyPointSelector.currentIndex = defaultStateValues.defaultKeyPointIndex;
    winConditionSelector.currentIndex = defaultStateValues.defaultWinConditionIndex;
    displayHintSelector.currentIndex = defaultStateValues.defaultTableHintIndex;
    inputModeSelector.currentIndex = defaultStateValues.defaultInputModeIndex;
}

function setAttempts(value)
{
    var mode = convertInputStringToHex(value);
    if(mode === TournamentContext.scoreMode)
    {
        attemptSelector.contentValue = 1;
        attemptSelector.enabled = false;
    }
    else if(mode === TournamentContext.pointMode)
    {
        attemptSelector.contentValue = defaultStateValues.defaultNumberOfThrows;
        attemptSelector.enabled = true;
    }
}
