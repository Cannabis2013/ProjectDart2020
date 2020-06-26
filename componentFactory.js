
function createSelectorKey(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("PushButton.qml");

    var buttonID = "button" + rowIndex;
    var button = component.createObject(parentID,
                                        {"id" : buttonID,
                                            "text" : keyText,
                                            "Layout.row" : rowIndex,
                                            "Layout.column" : columnIndex,
                                            "Layout.fillWidth" : true,
                                            "Layout.fillHeight" : true,
                                            "backgroundColor" : "black",
                                            "textColor" : "white",
                                            "buttonRadius" : 5,
                                            "isCheckable" : true,
                                            "checkedBackgroundColor" : "black",
                                            "checkedTextColor" : "white",
                                            "checkedScale" : 0.8});


    if(button === null)
        print("Something went wrong");

    return button;
}

function createNumberButton(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("PushButton.qml");

    var button = component.createObject(parentID,
                                        {"text" : keyText,
                                            "Layout.row" : rowIndex,
                                            "Layout.column" : columnIndex,
                                            "Layout.fillWidth" : true,
                                            "Layout.fillHeight" : true,
                                            "backgroundColor" : "black",
                                            "textColor" : "white",
                                            "buttonRadius" : 5});

    if(button === null)
        print("Something went wrong");

    return button;
}
