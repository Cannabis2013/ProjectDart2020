function addInput(modId, point) {
        if (inputMemory.inputs.length >= 3)
                return
        const input = {
                "modId": modId,
                "point": point
        }
        inputMemory.inputs.push(input)
        updateDisplay()
}

function updateDisplay() {
        const inputs = inputMemory.inputs
        inputsText.text = ""
        let txt = ""
        for (var i = 0; i < inputs.length; i++) {
                const input = inputs[i]
                txt += `${input.modId}${input.point}`
                if (i < inputs.length - 1)
                        txt += " "
        }
        inputsText.text = txt
}

function clearInputs() {
        inputsText.text = ""
        inputMemory.inputs = []
}
