pragma ComponentBehavior: Bound
import QtQuick 2.1
import QtQuick.Controls 6.0
import "../components"
import "../scripts/Game.js" as Script

Page {
  id: tournamentPage

  signal menuRequest

  background: Rectangle{
    color: "#1f1f1f"
  }
  header: PageHeader {
    buttonLabel: "Menu"
    height: 40
    onBack: tournamentPage.menuRequest()
    PushButton {
      label: "Restart"
      x: 81
      anchors.verticalCenter: parent.verticalCenter
      width: 64
      height: 32
      onClicked: restartDialog.visible = true
    }
  }

  QtObject {
    id: privateData
    property var inputs: []
  }
  ConfirmDialog {
    id: restartDialog
    onAccepted: Script.restartGame()
  }
  ConfirmDialog {
    id: proceedDialog
    onAccepted: Script.performReport()
  }
  Component {
    id: winnerScreen
    WinnerScreen {
      anchors.fill: parent
      onMenuRequest: tournamentPage.menuRequest()
      onRestartClicked: Script.restartGame()
      onUndoClicked: Script.undo()
      onClose: dialogLoader.sourceComponent = null
    }
  }
  Component {
    id: playersInfoScreen
    PlayersInfoScreen {
      anchors.fill: parent
      onClose: dialogLoader.sourceComponent = null
    }
  }
  InfoDisplay {
    id: infoDisplay
    anchors {top: parent.top;left: parent.left;}
    anchors.bottom: Script.isPortrait() ? turnControls.top : parent.bottom
    width: Script.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }
  TurnControls {
    id: turnControls
    anchors {bottom: keypad.top;left: keypad.left;margins: 8}
    onUndoClicked: Script.undo()
    onRedoClicked: Script.redo()
    onRestartClicked: restartDialog.visible = true
  }
  InputControls {
    id: inputControls
    anchors {bottom:keypad.top;right: keypad.right;margins:8}
    onPop: Script.popInput()
    onFlush: Script.resetScoreDisplay()
    onMiss: Script.addInput("S", 0)
  }
  KeyPad {
    id: keypad
    width: Script.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
    height: Script.isPortrait() ? 360 : parent.height - 40
    anchors {bottom: parent.bottom;right: parent.right}
    onEnter: (modId, point) => Script.addInput(modId, point)
    onReport: Script.reportInputs()
  }
  Loader {
    id: dialogLoader
    anchors.fill: parent
    asynchronous: true
    visible: status == Loader.Ready
  }

  Keys.onPressed: event => Script.handleCloseEvent(event)
  Component.onCompleted: Script.updateTurnValues()
  Component.onDestruction: dartsInitializer.saveState()
}
