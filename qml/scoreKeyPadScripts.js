/*
  Setup keypad
  */
function createKeyPad()
{
    // Create hotkeys
    createHotPadItems();
    // Create digits from 0 to 9
    createNumberPadItems();
}
function createHotPadItems()
{
    createColumn(1,3,0,[26,41,45]);
    createColumn(1,3,4,[60,85,100]);
    createRow(0,1,0,[25,50]);
    createRow(3,4,0,[170,180]);
}

function createColumn(startRow, endRow, column, labels)
{
    for(var i = startRow;i<= endRow;i++)
    {
        let keyLabel = labels[i - startRow];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,i,column);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
        keyPadBody.enableHotPads.connect(hotKeyPad.enableButton);
    }
}

function createRow(startColumn, endColumn, row, labels)
{
    for(var i = startColumn;i<= endColumn;i++)
    {
        let keyLabel = labels[i - startColumn];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,row,i);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
        keyPadBody.enableHotPads.connect(hotKeyPad.enableButton);
    }
}

function createNumberPadItems()
{
    var initialNumberPadRow = 1;
    var initialColumn = 3;
    var keyText = 1;
    for(var j = initialNumberPadRow;j <= 3;j++){
        for(var k = 1;k <= 3;k++){
            let numberKey = ComponentFactory.createNumberButton(keyPadLayout,keyText++,j,k);
            numberKey.clickedAndSendText.connect(keyPadBody.internalKeyClicked);
            keyPadBody.enableKeyPad.connect(numberKey.enableButton);
        }
        initialColumn = 3;
    }
    /*
      '0' numberpad
      */
    let numberKey = ComponentFactory.createNumberButton(keyPadLayout,0,4,2);
    numberKey.clickedAndSendText.connect(keyPadBody.internalKeyClicked);
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
