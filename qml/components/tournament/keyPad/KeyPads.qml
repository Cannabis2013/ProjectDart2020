import QtQuick 2.15
import QtQuick.Layouts 1.3

import "../../../components/geometry"
import "../../../components/buttons"
import "keyPadBuilder.js" as Builder

TransparentRect {
        id: keyPadRect

        enabled: false

        signal reportScore(string modId, int point)

        signal numberClicked(int point)
        onNumberClicked: point => {
                                 const modId = modKeys.selectedId()
                                 modKeys.unSelectAll()
                                 reportScore(modId, point)
                         }

        signal specialClicked(string value)
        onSpecialClicked: value => {
                                  modKeys.unSelectAll()
                                  reportScore("S", value)
                          }

        signal modKeyClicked(string modId)
        onModKeyClicked: modId => {
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
                id: middlePadGrid
                anchors.fill: parent
                rows: 4
                columns: 5
                columnSpacing: 0
                rowSpacing: 0
                flow: GridLayout.LeftToRight
                layoutDirection: Qt.RightToLeft
        }

        Component.onCompleted: Builder.buid()
}
