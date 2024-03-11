function setMessages(messages) {
        messageContainer.children = []
        for (var i = 0; i < messages.length; i++) {
                const message = messages[i]
                if (message !== "")
                        addMessage(message)
        }
}

function addMessage(message) {
        const comp = Qt.createComponent("CompMessage.qml")
        comp.createObject(messageContainer, {
                                  "icon": message.iconUrl,
                                  "message": message.content
                          })
}
