function createKeyPad()
{
    // Create hotkeys
    createHotPadItems();
    // Create digits from 0 to 9
    createNumberPadItems();
}
function createHotPadItems()
{
    createColumn(0,4,0,[50,45,41,26,25]);
    createColumn(0,4,4,[100,120,150,170,180]);
    createHotPad(60,60,0,1);
    createHotPad(85,85,0,3);
}

function createHotPad(keyLabel,value,row,column)
{
    let hotKeyPad = ComponentFactory.createHotPad(keyPadLayout,keyLabel,keyLabel,row,column,"green");
    hotKeyPad.keyPadClicked.connect(keyPadBody.internalHotKeyClicked);
    keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
    keyPadBody.enableHotPads.connect(hotKeyPad.enableButton);
}

function createColumn(startRow, endRow, column, labels)
{
    for(var row = startRow;row<= endRow;row++)
    {
        let keyLabel = labels[row - startRow];
        createHotPad(keyLabel,keyLabel,row,column);
    }
}

function createRow(startColumn, endColumn, row, labels)
{
    for(var column = startColumn;column<= endColumn;column++)
    {
        let keyLabel = labels[column - startColumn];
        createHotPad(keyLabel,keyLabel,row,column);
    }
}

function createNumberPadItems()
{
    var initialNumberPadRow = 1;
    var initialColumn = 3;
    var keyText = 1;
    for(var j = initialNumberPadRow;j <= 3;j++){
        for(var k = 1;k <= 3;k++){
            let value = keyText++;
            let numberKey = ComponentFactory.createNumberPad(keyPadLayout,value,value,j,k,"brown");
            numberKey.keyPadClicked.connect(keyPadBody.internalKeyClicked);
            keyPadBody.enableKeyPad.connect(numberKey.enableButton);
        }
        initialColumn = 3;
    }
    /*
      '0' numberpad
      */
    let numberKey = ComponentFactory.createNumberPad(keyPadLayout,0,0,4,2,"brown");
    numberKey.keyPadClicked.connect(keyPadBody.internalKeyClicked);
    keyPadBody.enableKeyPad.connect(numberKey.enableButton);
}

function handleNumberPadClicked(value)
{
    var currentValue = scoreView.currentText;
    if(currentValue.length >= 3)
        return;
    else if(currentValue.length === 0 && value === 0)
        return;
    scoreView.appendCharacter(value);
    if(currentValue.length === 1 && currentValue > 1)
        handleSubmitpadClicked();
    else if(currentValue.length === 2)
        handleSubmitpadClicked();
}

function handleClearPadClicked()
{
    var currentValue = scoreView.currentText;
    if(currentValue.length <= 0)
        return;
    scoreView.clearView();
}

function handleScoreViewValueChanged(text)
{
    updateSubmitPad(text);
    updateHotPads(text);
}

function updateSubmitPad(text)
{
    if(text.length > 0)
        submitPad.text = submitPadTextValues.scoreEnted;
    else
        submitPad.text = submitPadTextValues.noScoreEnted;
}

function updateHotPads(text)
{
    if(text.length > 0)
        keyPadBody.enableHotPads(false);
    else
        keyPadBody.enableHotPads(true);
}

function handleSubmitpadClicked()
{
    var currentText = scoreView.currentText;
    scoreView.clearView();
    sendInput(currentText,0x1);

}
