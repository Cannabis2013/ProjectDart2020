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
    onBack: tournamentPage.menuRequest()

    buttonLabel: "Menu"

    PushButton {
      onClicked: restartDialog.visible = true

      width: 104
      height: 48
      anchors{
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 8
      }
      label: "Restart"
      labelSize: 24
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
    anchors {
      top: parent.top
      right: Script.isPortrait() ? parent.right : parent.horizontalCenter
      bottom: Script.isPortrait() ? turnControls.top : parent.bottom
      left: parent.left
    }
    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }
  TurnControls {
    id: turnControls

    onUndoClicked: Script.undo()
    onRedoClicked: Script.redo()
    onRestartClicked: restartDialog.visible = true

    anchors {
      bottom: keypad.top
      left: keypad.left
      leftMargin: 8
    }
    height: 64
    width: 73
  }
  InputControls {
    id: inputControls

    width: 258
    height: 64
    anchors {
      bottom:keypad.top
      right: keypad.right
      rightMargin: 8
    }
    onPop: Script.popInput()
    onFlush: Script.resetScoreDisplay()
    onMiss: Script.addInput("S", 0)
  }
  KeyPad {
    id: keypad
    height: Script.isPortrait() ? 360 : parent.height - 64
    anchors {
      right: parent.right
      bottom: parent.bottom
      left: Script.isPortrait() ? parent.left : parent.horizontalCenter
    }
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
}
