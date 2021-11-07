function createConfirmPopUp(parentId, acceptSlot)
{
    var component = Qt.createComponent('ConfirmActionPopUp.qml',parentId);
    var properties = {
        "x" : 0,
        "y" : 0,
        "parent" : parentId
     };
    var instantiatedObject = component.createObject(parentId,properties);
    if(instantiatedObject === null)
        printNullObjectErrorMessage();
    instantiatedObject.acceptClicked.connect(acceptSlot);
    return instantiatedObject;
}

function printNullObjectErrorMessage()
{
    print("Something went very wrong. Call the police if necessary.");
    throw "Something went very wrong. Call the police if necessary.";
}
