import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPad"
import "keyPadDisplays"
import "compInputs.js" as Scripts

Item {
  id: keyPadRect

  signal reportInputs(var inputs)
  signal reportPreview(var inputs)

  signal clearDisplay
  onClearDisplay: Scripts.flushInputs()

  KeyPadDisplays {
    id: inputsDisplay
    width: parent.width
    height: 32
    anchors.top: parent.top
    anchors.leftMargin: 6
    anchors.rightMargin: 6
    onClearClicked: Scripts.flushInputs()
    onPopClicled: Scripts.popInput()
  }

  KeyPad {
    id: keyPad
    width: parent.width
    anchors.top: inputsDisplay.bottom
    anchors.bottom: parent.bottom
    onReportInputs: Scripts.report()
    onNumberClicked: function (modId, point) {
      Scripts.updateDisplay(modId, point)
    }
  }
}
