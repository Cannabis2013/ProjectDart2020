function setHiddenDarts(count) {
        const children = dartsLayout.children
        for (var i = children.length - 1; i >= 0; i--) {
                const child = children[i]
                child.visible = i >= count
        }
}
