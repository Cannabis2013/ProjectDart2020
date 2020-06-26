
function createSelectorKey(parentID,keyText, rowIndex, columnIndex) {
    var component = Qt.createComponent("PushButton.qml");

    var button = component.createObject(parentID,
                                        {"text" : keyText,
                                            "Layout.row" : rowIndex,
                                            "Layout.column" : columnIndex,
                                            "Layout.fillWidth" : true,
                                            "Layout.fillHeight" : true,
                                            "backgroundColor" : "black",
                                            "textColor" : "white",
                                            "buttonRadius" : 5,
                                            "isCheckable" : true});


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
