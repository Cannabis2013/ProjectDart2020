function stateChanged()
{
    var selectedIndexes = playersListView.currentIndexes();
    var selectedIndexesLength = selectedIndexes.length;
    var tournamentTitle = titleEdit.currentValue;
    var tournamentTitleLength = tournamentTitle.length;
    var status = selectedIndexesLength > 0 && tournamentTitleLength > 0;
    buttonsComponent.buttonTwoEnabled = status;
}

function addPlayer(playerName,email)
{
    playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
}
function gameModeToHex(text)
{
    var gameModes = stringModels.gameModes;
    if(text === gameModes[0])
        return 0x1;
}
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
        return DataModelContext.singleThrowInput;
    else if(hint === hints[1])
        return DataModelContext.multiThrowInput;
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


function initializeComponents(){
    throwSpinBox.contentValue = defaultStateValues.defaultNumberOfThrows;
    keyPointEdit.model = stringModels.fTPKeyPoints;;
    keyPointEdit.contentValue = defaultStateValues.defaultKeyPointIndex;
    displayHintSelector.contentValue = defaultStateValues.defaultTableHintIndex;
    winConditionSelector.contentValue = defaultStateValues.defaultWinConditionIndex;
    var df = defaultStateValues.defaultInputModeIndex;
    inputModeSelector.contentValue = df;
}

function acceptAndAdd(){
    var gameModeString = gameModeSelector.currentValue;
    var gameMode = gameModeToHex(gameModeString);
    if(gameMode === 0x1)
        assembleAndSendFTPTournament();
}

function assembleAndSendFTPTournament()
{
    var indexes = playersListView.currentIndexes();
    if(indexes.length <= 0)
        return;
    buttonsComponent.buttonTwoEnabled = false;
    var title = titleEdit.currentValue;
    // Declare array
    var arguments = [];
    // Convert values
    var gameMode = gameModeSelector.currentValue;
    var winConditionKeyIdentifier = winConditionSelector.currentValue;
    var displayHintSelectorValue = displayHintSelector.currentValue;
    var inputModeSelectorValue = inputModeSelector.currentValue;
    // Add values to array
    arguments[0] = gameModeToHex(gameMode);
    arguments[1] = keyPointEdit.currentValue;
    arguments[2] = convertKeyModifierToHex(winConditionKeyIdentifier);
    arguments[3] = convertHintToHex(displayHintSelectorValue);
    arguments[4] = convertInputStringToHex(inputModeSelectorValue);
    arguments[5] = throwSpinBox.currentValue;
    // Send values
    createBody.sendFTPDetails(title,
                              arguments,
                              indexes);
}
