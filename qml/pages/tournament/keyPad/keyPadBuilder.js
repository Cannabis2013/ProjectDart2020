function build() {
        const columnSpace = middlePadGrid.columnSpacing
        const rowSpace = middlePadGrid.rowSpacing
        const padWidth = keyPadRect.width / 5 - 4 * columnSpace
        const padHeight = keyPadRect.height / 5 - 4 * rowSpace
        buildNumbers(padWidth, padHeight)
}

function buildNumbers(width, height) {
        let totalButtons = 24
        let buttonIndex = 20
        while (totalButtons >= 0) {
                if (totalButtons === 4)
                        createBustPad(height, width, middlePadGrid)
                else if (totalButtons === 9)
                        createBullPad(height, width, middlePadGrid)
                else if (totalButtons === 14)
                        createBullsPad(height, width, middlePadGrid)
                else if (totalButtons === 19)
                        createModPad("D", height, width, middlePadGrid)
                else if (totalButtons === 24)
                        createModPad("T", height, width, middlePadGrid)
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
                                                      "width": width,
                                                      "backgroundColor": "white"
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
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width,
                                                      "text": "25",
                                                      "padValue": 25,
                                                      "backgroundColor": "green"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
}

function createBullsPad(height, width, parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width,
                                                      "text": "50",
                                                      "padValue": 50,
                                                      "backgroundColor": "red"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
}

function createBustPad(height, width, parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "height": height,
                                                      "width": width,
                                                      "text": "0",
                                                      "padValue": 0,
                                                      "backgroundColor": "orange"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
        object.padLongClicked.connect(keyPadRect.bustTurn)
}
