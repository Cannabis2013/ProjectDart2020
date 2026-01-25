pragma ComponentBehavior: Bound
import QtQuick 2.1
import QtQuick.Controls 6.0
import "../components"
import "../scripts/Game.js" as Script

Page {
  id: tournamentPage

  signal menuRequest

  QtObject {
    id: privateData
    property var inputs: []
  }

  Keys.onPressed: event => handleCloseEvent(event)

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

  InfoDisplay {
    id: infoDisplay
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: messageSection.top
    width: Script.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }

  MessagesDisplay {
    id: messageSection
    anchors.left: parent.left
    anchors.bottom: Script.isPortrait() ? turnControls.top : parent.bottom
    anchors.margins: 8
    width: Script.isPortrait() ? parent.width : parent.width / 2
    height: 64
  }

  TurnControls {
    id: turnControls

    anchors.bottom: keypad.top
    anchors.left: keypad.left
    anchors.margins: 8

    onUndoClicked: Script.undo()
    onRedoClicked: Script.redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls

    anchors.bottom: keypad.top
    anchors.right: keypad.right
    anchors.margins: 8

    onPop: Script.popInput()
    onFlush: Script.resetScoreDisplay()
    onMiss: Script.addInput("S", 0)
  }

  KeyPad {
    id: keypad
    width: Script.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
    height: Script.isPortrait() ? 360 : parent.height - 40
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    onEnter: (modId, point) => Script.addInput(modId, point)
    onReport: Script.reportInputs()
  }

  Loader {
    id: dialogLoader
    anchors.fill: parent
    asynchronous: true
    visible: status == Loader.Ready
  }

  Component.onCompleted: Script.updateTurnValues()
  Component.onDestruction: dartsInitializer.saveState()
}
