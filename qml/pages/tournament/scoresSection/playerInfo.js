function showCounter(status) {
        const dartsCounter = dartsContainer.children[0]
        if (status && !dartsCounter) {
                const comp = Qt.createComponent("DartsCounter.qml")
                const obj = comp.createObject(dartsContainer)
        } else if (!status && dartsCounter) {
                dartsCounter.destroy()
        }
}

function updateDartArrows(count) {
        const turnCounter = dartsContainer.children[0]
        turnCounter.setVisibleDarts(count)
}
