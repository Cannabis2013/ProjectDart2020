pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
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
    id: inputs
    property var all: []
  }
  ConfirmDialog {
    id: restartDialog
    onAccepted: Script.restartGame()
  }
  ConfirmDialog {
    id: proceedDialog
    onAccepted: {
      Script.addInputsAndProceed()
      Script.update()
    }
  }
  Component {
    id: winnerScreen
    WinnerScreen {
      anchors.fill: parent
      onMenuRequest: tournamentPage.menuRequest()
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
  QtObject{
    id: colors
    readonly property color bg: "#2f2f2f"
    readonly property color bright: "#3f3f3f"
  }
  ColorAnimation {
    id: backgroundAnimation
    from: colors.bg
    to: colors.bright
    target: infoRect
    property: "color"
    duration: 1500
    loops: ColorAnimation.Infinite
    easing.type: Easing.SineCurve
  }
  Rectangle{
    id: infoRect
    radius: Script.isPortrait() ? 8 : 0
    color: colors.bg
    anchors {
      top: parent.top
      right: Script.isPortrait() ? parent.right : parent.horizontalCenter
      bottom: Script.isPortrait() ? turnControls.top : parent.bottom
      left: parent.left
    }
    ScoreDisplay {
      id: scoreDisplay
      width: parent.width
      anchors {
        top: parent.top
        bottom: inputsDisplay.top
        margins: 8
      }
      onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
    }
    InputsDisplay{
      id: inputsDisplay
      width: parent.width
      height: 56
      anchors{
        bottom: finishDisplay.top
        margins: 8
      }
    }
    FinishDisplay {
      id: finishDisplay
      anchors.bottom: statsDisplay.top
      anchors.margins: 8
      height: 56
      width: parent.width
    }
    StatsDisplay{
      id: statsDisplay
      clip: true
      width: parent.width
      height: 56
      anchors{
        bottom: parent.bottom
        margins: 8
      }
    }
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
    onFlush: Script.update()
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
  Component.onCompleted: Script.updateDisplays()
}
