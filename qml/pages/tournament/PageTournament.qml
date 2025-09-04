import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "turnControls"
import "keyPad"
import "inputControls"
import "messages"
import "scoreDisplay"
import "pageTournament.js" as Scripts
import "screens"
import "dialogs"

Page {
  id: tournamentPage
  signal menuRequest

  QtObject {
    id: pageDimensions
    property real width: Scripts.isPortrait() ? parent.width : parent.width / 2
  }

  focus: true
  Keys.onPressed: event => Scripts.handleCloseEvent(event)

  ConfirmDialog{
    id: restartDialog
    onAccepted: Scripts.restartGame()
  }

  ConfirmDialog{
    id: proceedDialog
    onAccepted: Scripts.performReport()
  }

  Component{
    id: winnerScreen

    WinnerScreen{
      anchors.fill: parent

      onRestartClicked: Scripts.restartGame()
      onUndoClicked: Scripts.undo()
      onClose: dialogLoader.sourceComponent = null
    }
  }

  Component{
    id: playersInfoScreen
    PlayersInfoScreen{
      anchors.fill: parent

      onClose: dialogLoader.sourceComponent = null
    }
  }

  ScoreDisplay {
    id: scoreDisplay

    anchors.top: parent.top
    anchors.left: parent.left

    height: 146
    width: pageDimensions.width

    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }

  MessagesDisplay {
    id: messageSection
    anchors.top: scoreDisplay.bottom
    anchors.left: parent.left
    width: pageDimensions.width
    height: 48
  }

  TurnControls {
    id: turnControls
    anchors.top: messageSection.bottom
    anchors.left: parent.left
    width: pageDimensions.width
    height: 48
    onUndoClicked: Scripts.undo()
    onRedoClicked: Scripts.redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls
    anchors.top: Scripts.isPortrait() ? turnControls.bottom : parent.top
    anchors.right: parent.right
    width: pageDimensions.width
    onPop: Scripts.pop()
    onFlush: Scripts.resetScoreDisplay()
    height: 52
  }

  KeyPad {
    id: inputSection
    width: pageDimensions.width
    anchors.top: inputControls.bottom
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    onEnter: (modId, point) => Scripts.addInput(modId, point)
    onReport: Scripts.reportInputs()
  }

  Loader{
    id: dialogLoader
    anchors.fill: parent
    asynchronous: true
    visible: status == Loader.Ready
  }

  Component.onCompleted: Scripts.updateTurnValues()
  Component.onDestruction: dartsInitializer.saveState()
}
