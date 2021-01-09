function createNumberButton(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("KeyPadItem.qml");
    var properties = {
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "Layout.fillWidth" : true,
        "Layout.fillHeight" : true,
        "backgroundColor" : "white",
        "textColor" : "black",
        "type" : TournamentContext.numberPad
    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}

function createHotKeyButton(parentID,keyText, rowIndex, columnIndex)
{
    var component = Qt.createComponent("KeyPadItem.qml");
    var properties = {
        "text" : keyText,
        "Layout.row" : rowIndex,
        "Layout.column" : columnIndex,
        "Layout.fillWidth" : true,
        "Layout.fillHeight" : true,
        "backgroundColor" : "green",
        "type" : TournamentContext.hotKeyPad
    };
    var button = component.createObject(parentID,properties);
    if(button === null)
        throw "Something went wrong";
    return button;
}
