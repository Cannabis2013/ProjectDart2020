
function createModifier(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("PushButton.qml");

    var buttonID = "button" + rowIndex;
    var properties = {
        "id" : buttonID,
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "Layout.fillWidth" : true,
        "Layout.fillHeight" : true,
        "backgroundColor" : "blue",
        "textColor" : "white",
        "buttonRadius" : 5,
        "fontSize" : 16,
        "isCheckable" : true,
        "checkedBackgroundColor" : "darkblue",
        "checkedTextColor" : "white",
        "checkedScale" : 0.8,
        "hoverEnabled" : false,
        "enabled" : false
    };
    var button = component.createObject(parentID,properties);

    if(button === null)
        print("Something went wrong");

    return button;
}

function createNumberButton(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("KeyPadItem.qml");
    var properties = {
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "Layout.fillWidth" : true,
        "Layout.fillHeight" : true,
        "Layout.fillHeight" : true,

    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}

function createPopUp(parentID, id,fileName,x, y, width, height)
{
    var component = Qt.createComponent(fileName);
    var properties = {
        "id" : id,
        "x" : x,
        "y" : y,
        "width" : width,
        "height" : height,
        "anchors.fill" : parentID
     };
    var createPlayerPopUp = component.createObject(parentID, properties);
    if(createPlayerPopUp === null)
        print("Something went very wrong. Call the police if necessary.");
    return createPlayerPopUp;
}

function createConfirmPopUp(fileName, parentID)
{
    var component = Qt.createComponent(fileName);
    var properties = {
        "x" : 0,
        "y" : 0,
        "width" : parentID.width,
        "height" : parentID.height,
        "anchors.fill" : parentID,
        "isPopUp" : true
     };
    var instantiatedObject = component.createObject(parentID, properties);
    if(instantiatedObject === null)
        print("Something went very wrong. Call the police if necessary.");
    return instantiatedObject;
}
