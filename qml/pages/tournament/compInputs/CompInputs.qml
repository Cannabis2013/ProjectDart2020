import QtQuick 2.15
import QtQuick.Layouts 1.3
import "keyPadBuilder.js" as Builder
import "compInputs.js" as Scripts

Item {
        id: keyPadRect

        signal reportScore(string modId, int point)
        signal bustTurn(int value)

        signal numberClicked(int point)
        onNumberClicked: point => Scripts.handleNumberPadClicked(point)

        signal specialClicked(string value)
        onSpecialClicked: value => Scripts.handleSpecialPadClicked(value)

        signal modKeyClicked(string modId)
        onModKeyClicked: modId => Scripts.handleModPadClicked(modId)

        QtObject {
                id: modKeys
                property var modObjects: []
        }

        signal buttonClicked

        GridLayout {
                id: middlePadGrid
                anchors.fill: parent
                columns: 5
                columnSpacing: 0
                rowSpacing: 0
                layoutDirection: Qt.RightToLeft
        }

        Component.onCompleted: Builder.build()
}
