function build() {
        let buttonIndex = 24
        let numberIndex = 20
        while (buttonIndex >= 0) {
                if (buttonIndex === 4)
                        createBustPad(middlePadGrid)
                else if (buttonIndex === 9)
                        createBullPad(middlePadGrid)
                else if (buttonIndex === 14)
                        createBullsPad(middlePadGrid)
                else if (buttonIndex === 19)
                        createModPad("D", middlePadGrid)
                else if (buttonIndex === 24)
                        createModPad("T", middlePadGrid)
                else {
                        createNumberPad(numberIndex, numberIndex, middlePadGrid)
                        numberIndex--
                }
                buttonIndex--
        }
}

function createNumberPad(padValue, textDisplay, parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "text": textDisplay,
                                                      "padValue": padValue,
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "backgroundColor": "white"
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}

function createModPad(modId, parentObj) {
        const component = Qt.createComponent("ModPad.qml")
        const modKey = component.createObject(parentObj, {
                                                      "text": modId,
                                                      "modId": modId,
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true
                                              })
        modKeys.modObjects.push(modKey)
        modKey.modClicked.connect(modKeyClicked)
}

function createBullPad(parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "text": "25",
                                                      "padValue": 25,
                                                      "backgroundColor": "green"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
}

function createBullsPad(parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "text": "50",
                                                      "padValue": 50,
                                                      "backgroundColor": "red"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
}

function createBustPad(parentObj) {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(parentObj, {
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "text": "0",
                                                      "padValue": 0,
                                                      "backgroundColor": "orange"
                                              })
        object.padClicked.connect(keyPadRect.specialClicked)
        object.padLongClicked.connect(keyPadRect.bustTurn)
}
