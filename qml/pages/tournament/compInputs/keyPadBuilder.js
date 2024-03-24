function build() {
        let buttonIndex = 24
        let numberIndex = 20
        while (buttonIndex >= 0) {
                if (buttonIndex === 4)
                        createReportPad()
                else if (buttonIndex === 9)
                        createNumberPad(25, 25, "green")
                else if (buttonIndex === 14)
                        createNumberPad(50, 50, "red")
                else if (buttonIndex === 19)
                        createModPad("D")
                else if (buttonIndex === 24)
                        createModPad("T")
                else {
                        createNumberPad(numberIndex, numberIndex)
                        numberIndex--
                }
                buttonIndex--
        }
}

function createNumberPad(padValue, textDisplay, color = "white") {
        const component = Qt.createComponent("NumberPad.qml")
        const object = component.createObject(middlePadGrid, {
                                                      "text": textDisplay,
                                                      "padValue": padValue,
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "color": color
                                              })
        object.padClicked.connect(keyPadRect.numberClicked)
}

function createModPad(modId) {
        const component = Qt.createComponent("ModPad.qml")
        const modKey = component.createObject(middlePadGrid, {
                                                      "text": modId,
                                                      "modId": modId,
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true
                                              })
        modKeys.modObjects.push(modKey)
        modKey.modClicked.connect(modKeyClicked)
}

function createReportPad() {
        const component = Qt.createComponent("Pad.qml")
        const object = component.createObject(middlePadGrid, {
                                                      "Layout.fillWidth": true,
                                                      "Layout.fillHeight": true,
                                                      "text": "=>",
                                                      "color": "orange"
                                              })
        object.clicked.connect(keyPadRect.reportScore)
}
