function handleDoubleKeyPressed(check){
    if(modifiers.isTrippleModifierPressed)
        trippleModifier.clicked();
    modifiers.isDoubleModifierPressed = check;
}
function handleTrippleKeyPressed(check){
    if(modifiers.isDoubleModifierPressed)
        doubleModifier.clicked();
    modifiers.isTrippleModifierPressed = check;
}

function handleNumberKeyPressed(text)
{
    keyPadBody.internalKeyClicked(text);
}

function isModifiersPressed()
{
    var doubleChecked = modifiers.isDoubleModifierPressed;
    var trippleChecked = modifiers.isTrippleModifierPressed;
    return doubleChecked || trippleChecked;
}

function assembleKeyPad()
{
    var columnCount = keyPadLayout.columns;
    var rowCount = keyPadLayout.rows;
    var count = 0;
    var keyText = 0;
    var initialColumn = 2;

    var strings = ["D","T"];
    // Modifiers
    for(var r = 0;r < 2 ;r++){
        var selectorKey = ComponentFactory.createModifier(keyPadLayout,strings[r],0,r);
        keyPadBody.enableKeyPad.connect(selectorKey.setEnabled);
        if(selectorKey.text === "D")
        {
            selectorKey.checkStateChanged.connect(handleDoubleKeyPressed);
            doubleModifier = selectorKey;
        }
        else if(selectorKey.text === "T")
        {
            selectorKey.checkStateChanged.connect(handleTrippleKeyPressed);
            trippleModifier = selectorKey;
        }
    }
    /*
      Numberpads
        - Digits from 0  to 20
      */
    for(var i = 0;i < rowCount && keyText < 21;i++){
        for(var j = initialColumn;j < columnCount && keyText < 21;j++){
            var numberKey = ComponentFactory.createNumberButton(keyPadLayout,keyText++,i,j);
            numberKey.clickedAndSendText.connect(keyPadBody.internalKeyClicked);
            keyPadBody.enableKeyPad.connect(numberKey.setEnabled);
        }
        initialColumn = 0;
    }
}
