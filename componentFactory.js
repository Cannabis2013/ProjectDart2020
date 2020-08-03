
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
    var component = Qt.createComponent("PushButton.qml");
    var properties = {
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "Layout.fillWidth" : true,
        "Layout.fillHeight" : true,
        "Layout.fillHeight" : true,
        "backgroundColor" : "black",
        "textColor" : "white",
        "fontSize" : 16,
        "buttonRadius" : 5,
        "pressedScale" : 0.75,
        "hoveredColor" : "black",
        "enabled" : false
    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}

function createPopUp(parentID, id,x, y, width, height)
{
    var component = Qt.createComponent("CreatePlayerPopUp.qml");
    var properties = {
        "id" : id,
        "x" : x,
        "y" : y,
        "width" : width,
        "height" : height,
        "anchors.fill" : applicationWindow
     };
    var createPlayerPopUp = component.createObject(parentID, properties);
    if(createPlayerPopUp === null)
        print("Something went very wrong. Call the police if necessary.");
    return createPlayerPopUp;
}

