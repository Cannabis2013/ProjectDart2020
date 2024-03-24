import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPadBuilder.js" as Builder
import "compInputs.js" as Scripts

Item {
        id: keyPadRect

        signal reportScores(var scores)
        signal reportScore
        onReportScore: Scripts.report()
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

        InputDisplay {
                id: inputsDisplay
                height: 64
                width: parent.width
        }

        GridLayout {
                id: middlePadGrid
                anchors.top: inputsDisplay.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                columns: 5
                columnSpacing: 0
                rowSpacing: 0
                layoutDirection: Qt.RightToLeft
        }

        Component.onCompleted: Builder.build()
}
