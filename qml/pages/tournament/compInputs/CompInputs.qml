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

        signal numberClicked(string modId, int point)
        onNumberClicked: (modId, point) => inputsDisplay.addInput(modId, point)

        InputDisplay {
                id: inputsDisplay
                height: 64
                width: parent.width
        }

        KeyPad {
                id: keyPad
                anchors.top: inputsDisplay.bottom
                anchors.bottom: parent.bottom
                width: parent.width
        }
}
