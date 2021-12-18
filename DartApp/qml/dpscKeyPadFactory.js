function createNumberPad(parentID,label,itemValue,row,column,backgroundColor) {
    var component = Qt.createComponent("KeyPadItem.qml");
    var properties = {
        "text" : label,
        "padValue" : itemValue,
        "Layout.row" : row,
        "Layout.column" : column,
        "pressedColor" : backgroundColor,
        "backgroundColor" : backgroundColor,
        "type" : TournamentContext.numberPad
    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}

function createModPad(parentID,label, rowIndex, columnIndex) {
    var component = Qt.createComponent("KeyPadItem.qml");

    var buttonID = "button" + rowIndex;
    var properties = {
        "id" : buttonID,
        "text" : label,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "backgroundColor" : "blue",
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
