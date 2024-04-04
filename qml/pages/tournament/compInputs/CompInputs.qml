import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPad"
import "keyPadDisplays"
import "compInputs.js" as Scripts

Item {
        id: keyPadRect

        signal reportScores(var scores)
        signal reportScore
        onReportScore: Scripts.report()

        signal clearDisplay
        onClearDisplay: Scripts.reset()

        signal numberClicked(string modId, int point)
        onNumberClicked: (modId, point) => Scripts.handleInput(modId, point)

        KeyPadDisplays {
                id: inputsDisplay
                height: 64
                anchors.top: parent.top
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.leftMargin: 12
                onDisplayCleared: scorePreview.clear()
                onDisplayPopped: score => scorePreview.updateScore(score)
        }

        KeyPad {
                id: keyPad
                anchors.top: inputsDisplay.bottom
                anchors.topMargin: 6
                anchors.bottom: parent.bottom
                width: parent.width
        }
}
