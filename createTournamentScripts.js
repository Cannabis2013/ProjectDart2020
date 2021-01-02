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
        return DataModelContext.singleDimensional;
    else if(hint === hints[1])
        return DataModelContext.multiDimensional;
    else
        return -1;
}

function createStringModel()
{
    var text = gameModeSelector.currentValue;
    var gameMode = gameModeToHex(text);
    if(gameMode === 0x1)
        return stringModels.firstToPostPointValues;

    return [];
}

function initializeKeyPointComponent(){
    keyPointEdit.model = createStringModel();
    keyPointEdit.currentIndex = defaultStateValues.defaultKeyPointIndex;
}

function acceptAndAdd(){
    var indexes = playersListView.currentIndexes();
    if(indexes.length <= 0)
        return;
    buttonsComponent.buttonTwoEnabled = false;
    var title = titleEdit.currentValue;
    var gameMode = gameModeSelector.currentValue;
    var gameCode = gameModeToHex(gameMode);
    var keyPoint = keyPointEdit.currentValue;
    var winConditionKeyIdentifier = winConditionSelector.currentValue;
    var winConditionKeyCode = convertKeyModifierToHex(winConditionKeyIdentifier);
    var modelDisplayHint = displayHintSelector.currentValue;
    var hint = convertHintToHex(modelDisplayHint);
    var numberOfThrows = throwSpinBox.currentValue;
    createBody.sendTournament(title,
                              numberOfThrows,
                              gameCode,
                              winConditionKeyCode,
                              keyPoint,
                              hint,
                              indexes);
}
