function createNumberPad(parentID, label, itemValue, row, column, backgroundColor) {
        var component = Qt.createComponent("KeyPadItem.qml")
        var properties = {
                "text": label,
                "padValue": itemValue,
                "Layout.row": row,
                "Layout.column": column,
                "pressedColor": backgroundColor,
                "backgroundColor": backgroundColor,
                "type": TournamentContext.numberPad
        }
        var button = component.createObject(parentID, properties)
        if (button === null)
                throw "Something went wrong"
        return button
}

function createHotPad(parentID, label, value, rowIndex, columnIndex, backgroundColor) {
        var component = Qt.createComponent("KeyPadItem.qml")

        var buttonID = "button" + rowIndex
        var properties = {
                "id": buttonID,
                "text": label,
                "padValue": value,
                "Layout.row": rowIndex,
                "Layout.column": columnIndex,
                "backgroundColor": backgroundColor,
                "enabled": false,
                "type": TournamentContext.hotPad
        }
        var button = component.createObject(parentID, properties)

        if (button === null)
                print("Something went wrong")

        return button
}
