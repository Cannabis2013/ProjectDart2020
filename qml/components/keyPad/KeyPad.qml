import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15
import "../../components/buttons"
import "keyPadBuilder.js" as Builder

Rectangle {
        id: keyPadRect
        clip: true
        color: "transparent"
        layer.enabled: true
        layer.effect: OpacityMask {
                maskSource: Rectangle {
                        width: keyPadRect.width
                        height: keyPadRect.height
                        radius: 12
                }
        }

        signal reportScore(string modId, string value)

        signal numberClicked(string value)
        onNumberClicked: {
                const modId = modKeys.selectedId()
                modKeys.unSelectAll()
                reportScore(modId, value)
        }

        signal modKeyClicked(string modId)
        onModKeyClicked: {
                const mods = modKeys.modObjects
                for (var i = 0; i < mods.length; i++) {
                        const mod = mods[i]
                        if (mod.modId !== modId)
                                mod.select(false)
                }
        }

        QtObject {
                id: modKeys
                property var modObjects: []

                function selectedId() {
                        for (var i = 0; i < modObjects.length; i++) {
                                const modObject = modObjects[i]
                                if (modObject.selected)
                                        return modObject.modId
                        }
                        return "S"
                }

                signal unSelectAll
                onUnSelectAll: {
                        for (var i = 0; i < modObjects.length; i++) {
                                const mod = modObjects[i]
                                mod.select(false)
                        }
                }
        }

        signal buttonClicked

        GridLayout {
                anchors.fill: parent
                rows: 3
                columns: 2
                columnSpacing: 0
                rowSpacing: 0
                flow: GridLayout.LeftToRight
                GridLayout {
                        id: middlePadGrid
                        rows: 4
                        columns: 5
                        columnSpacing: 0
                        rowSpacing: 0
                        flow: GridLayout.LeftToRight
                        layoutDirection: Qt.RightToLeft
                }
        }

        Component.onCompleted: Builder.buid()
}
