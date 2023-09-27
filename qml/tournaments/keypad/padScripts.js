function handleDoubleKeyPressed(check){
    if(modPads.isTrippleModifierPressed)
        modPads.trippleModifier.clicked();
    modPads.isDoubleModifierPressed = check;
    enableHotPads(!check);
}
function handleTrippleKeyPressed(check){
    if(modPads.isDoubleModifierPressed)
        modPads.doubleModifier.clicked();
    modPads.isTrippleModifierPressed = check;
    enableHotPads(!check);
}

function enableHotPads(status)
{
    hotPads.bustPad.enableButton(status)
    hotPads.bullPad.enableButton(status);
    hotPads.bullsEyePad.enableButton(status);
}

function handleNumberKeyPressed(text)
{
    keyPadBody.internalKeyClicked(text);
}

function isModifiersPressed()
{
    var doubleChecked = modPads.isDoubleModifierPressed;
    var trippleChecked = modPads.isTrippleModifierPressed;
    return doubleChecked || trippleChecked;
}

function createKeyPad()
{
    createNumberPads();
    createModPads();
    createHotPads();
}

function createNumberPads()
{
    var columnCount = keyPadLayout.columns;
    var label = 1;
    for(var i = 0;label < 21;i++){
        for(var j = 0;j < columnCount && label < 21;j++)
        {
            let val = label++;
            createNumberPad(val,val,i,j,"brown");
        }
    }
}

function createNumberPad(label,value,row,column,backgroundColor)
{
    var numberPad = ComponentFactory.createNumberPad(keyPadLayout,label,value,row,column,backgroundColor);
    numberPad.keyPadClicked.connect(keyPadBody.internalKeyClicked);
    keyPadBody.enableKeyPad.connect(numberPad.enableButton);
    return numberPad;
}

function createModPads()
{
    modPads.doubleModifier = createModPad("D",4,0,handleDoubleKeyPressed);
    modPads.trippleModifier = createModPad("T",4,1,handleTrippleKeyPressed);
}

function createModPad(label,row, column, func)
{
    var keyPadItem = ComponentFactory.createModPad(keyPadLayout,label,row,column);
    keyPadBody.enableKeyPad.connect(keyPadItem.enableButton);
    keyPadItem.checkStateChanged.connect(func);
    return keyPadItem;
}

function createHotPads(){
    hotPads.bustPad = createNumberPad("bust",0,4,2,"gray")
    hotPads.bullPad = createNumberPad(25,25,4,3,"green");
    hotPads.bullsEyePad = createNumberPad(50,50,4,4,"red");
}

function processInput(value)
{
    var modifierClickCode = modClickCode();
    if(modifierClickCode === 0x2B)
        modPads.doubleModifier.clicked();
    else if(modifierClickCode === 0x2C)
        modPads.trippleModifier.clicked();
    keyClicked(value,modifierClickCode);
}

function modClickCode()
{
    if(modPads.isTrippleModifierPressed)
        return 0x2C
    else if(modPads.isDoubleModifierPressed)
        return 0x2B;
    else
        return 0x2A;
}
