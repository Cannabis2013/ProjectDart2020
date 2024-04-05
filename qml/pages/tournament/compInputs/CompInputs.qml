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

        ColumnLayout {
                anchors.fill: parent
                KeyPadDisplays {
                        id: inputsDisplay
                        Layout.fillWidth: true
                        Layout.preferredHeight: 64
                        Layout.leftMargin: 6
                        Layout.rightMargin: 6
                        onDisplayCleared: scorePreview.clear()
                        onDisplayPopped: score => scorePreview.updateScore(score)
                }

                KeyPad {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }
        }
}
