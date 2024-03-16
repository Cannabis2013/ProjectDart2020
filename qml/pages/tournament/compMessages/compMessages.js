var finishUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png"
var deltaUrl = "qrc:/pictures/Ressources/Pictures/delta.png"

function updateMessages() {
        messageContainer.children = []
        const finishRow = dartsScores.finishRow()
        const delta = dartsScores.delta()
        if (finishRow.length > 0)
                addMessage(finishRow, finishUrl)
        addMessage(delta, deltaUrl)
}

function addMessage(message, url) {
        const comp = Qt.createComponent("CompMessage.qml")
        const obj = comp.createObject(messageContainer)
        obj.setValues(message, url)
}
