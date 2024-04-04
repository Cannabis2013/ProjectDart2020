var inputsMem = []

function hasInputs() {
        return inputsMem.length > 0
}

function readInputs() {
        return inputsMem
}

function addInput(modId, point) {
        if (inputsMem.length >= 3)
                return undefined
        const input = createInput(modId, point)
        inputsMem.push(input)
        updateDisplay()
        return input
}

function createInput(modId, point) {
        return {
                "modId": modId,
                "point": point
        }
}

function updateDisplay() {
        let text = ""
        inputsMem.forEach(input => text += `${input.modId}${input.point} `)
        textInputs.text = text
}

function popInput() {
        if (inputsMem.length <= 0)
                return undefined
        const input = inputsMem.pop()
        updateDisplay()
        return input
}

function clear() {
        inputsMem = []
        textInputs.text = ""
}
