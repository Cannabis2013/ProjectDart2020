
/*
  Setup keypad
  */
function createKeyPad()
{
    /*
      Various hotkeys
      */
    createHotPadItems();
    /*
      Numberpads
        - Digits from 0 to 9
      */
    createNumberPadItems();
}
function createHotPadItems()
{
    var leftLabels = [26,41,45];
    var rightLabels = [60,85,100];
    var upperLeftLabels = [25,50];
    var upperRightLabels = [170,180];
    for(var i = 1;i<= 3;i++)
    {
        let keyLabel = leftLabels[i - 1];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,i,0);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
    }
    for(var j = 1;j<= 3;j++)
    {
        let keyLabel = rightLabels[j - 1];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,j,4);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
    }
    for(var k = 0;k <=1;k++)
    {
        let keyLabel = upperLeftLabels[k];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,0,k);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
    }
    for(var l = 3;l <=4;l++)
    {
        let keyLabel = upperRightLabels[l -3];
        let hotKeyPad = ComponentFactory.createHotKeyButton(keyPadLayout,keyLabel,0,l);
        hotKeyPad.clickedAndSendText.connect(keyPadBody.internalHotKeyClicked);
        keyPadBody.enableKeyPad.connect(hotKeyPad.enableButton);
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
    if(text.length > 0)
        submitPad.text = submitPadTextValues.scoreEnted;
    else
        submitPad.text = submitPadTextValues.noScoreEnted;
}

function handleSubmitpadClicked()
{
    var currentText = scoreView.currentText;
    scoreView.clearView();
    sendInput(currentText,0x1);

}
