function update(turnObj, rowObj) {
        undoButton.enabled = turnObj.canUndo
        redoButton.enabled = turnObj.canRedo
        let text = ""
        text += `Turn: ${turnObj.turnIndex + 1}`
        if (rowObj && rowObj.finish.length > 0)
                text += ` - Row: ${rowObj.finish}`
        messageRect.text = text
}
