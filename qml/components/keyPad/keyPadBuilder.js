function buid() {
        const padWidth = keyPadRect.width / 5
        const padHeight = keyPadRect.height / 5
        buildNumbers(padWidth, padHeight)
}

function buildNumbers(width, height) {
        let totalButtons = 24
        let buttonIndex = 20
        while (totalButtons >= 0) {
                if (totalButtons === 0)
                        createModPad("T", height, width, middlePadGrid)
                else if (totalButtons === 1)
                        createModPad("D", height, width, middlePadGrid)
                else if (totalButtons === 2)
                        createBustPad(height, width, middlePadGrid)
                else if (totalButtons === 3)
                        createBullsPad(height, width, middlePadGrid)
                else if (totalButtons === 4)
                        createBullPad(height, width, middlePadGrid)
                else {
                        createNumberPad(buttonIndex, buttonIndex, height, width, middlePadGrid)
                        buttonIndex--
                }
                totalButtons--
        }
}

function createNumberPad(padValue, textDisplay, height, width, parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "text": textDisplay,
                                                      "padValue": padValue,
                                                      "height": height,
                                                      "width": width
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}

function createModPad(modId, height, width, parentObj) {
        const component = Qt.createComponent("ModPad.qml")
        const modKey = component.createObject(parentObj, {
                                                      "text": modId,
                                                      "modId": modId,
                                                      "height": height,
                                                      "width": width
                                              })
        modKeys.modObjects.push(modKey)
        modKey.modClicked.connect(modKeyClicked)
}

function createBullPad(height, width, parentObj) {
        const component = Qt.createComponent("BullPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}

function createBullsPad(height, width, parentObj) {
        const component = Qt.createComponent("BullsPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}

function createBustPad(height, width, parentObj) {
        const component = Qt.createComponent("BustPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}
