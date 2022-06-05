function createConfirmPopUp(parentId,cancelSlot, acceptSlot)
{
    var obj = createComponent(parentId);
    if(cancelSlot !== undefined)
        obj.cancelClicked.connect(cancelSlot);
    obj.acceptClicked.connect(acceptSlot);
    return obj;
}

function createComponent(parentId)
{
    var component = Qt.createComponent('ConfirmActionPopUp.qml',parentId);
    var properties = {
        "x" : 0,
        "y" : 0,
        "parent" : parentId
     };
    var instantiatedObject = component.createObject(parentId,properties);
    if(instantiatedObject === null)
    {
        printNullObjectErrorMessage();
        throw "Something went very wrong. Call the police if necessary.";
    }
    return instantiatedObject;
}

function printNullObjectErrorMessage()
{
    print("Something went very wrong. Call the police if necessary.");
}
