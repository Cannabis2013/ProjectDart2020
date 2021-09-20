
function createModifier(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("KeyPadItem.qml");

    var buttonID = "button" + rowIndex;
    var properties = {
        "id" : buttonID,
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "backgroundColor" : "blue",
        "textColor" : "white",
        "buttonRadius" : 5,
        "fontSize" : 16,
        "isCheckable" : true,
        "checkedTextColor" : "white",
        "checkedScale" : 0.8,
        "enabled" : false,
        "type" : TournamentContext.modiferPad
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
        "pressedColor" : "gray",
        "type" : TournamentContext.numberPad
    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}
