import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPad"
import "inputsDisplay"
import "compInputs.js" as Scripts

Item {
        id: keyPadRect

        signal reportScores(var scores)
        signal reportScore
        onReportScore: Scripts.report()

        signal updatePreview(int score)

        signal clearDisplay
        onClearDisplay: inputsDisplay.flushInputs()

        signal numberClicked(string modId, int point)
        onNumberClicked: (modId, point) => Scripts.handleInput(modId, point)

        InputDisplay {
                id: inputsDisplay
                height: 48
                width: parent.width
        }

        KeyPad {
                id: keyPad
                anchors.top: inputsDisplay.bottom
                anchors.bottom: parent.bottom
                width: parent.width
        }
}
