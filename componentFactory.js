
function createModifier(parentID,keyText, rowIndex, columnIndex) {
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
                                            "fontSize" : 16,
                                            "isCheckable" : true,
                                            "checkedBackgroundColor" : "white",
                                            "checkedTextColor" : "black",
                                            "checkedScale" : 0.8,
                                            "hoverEnabled" : false});


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
                                            "Layout.fillHeight" : true,
                                            "backgroundColor" : "black",
                                            "textColor" : "white",
                                            "fontSize" : 16,
                                            "buttonRadius" : 5,
                                            "pressedScale" : 0.75,
                                            "hoveredColor" : "black"});

    if(button === null)
        print("Something went wrong");

    return button;
}
