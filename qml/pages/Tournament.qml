import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../components/turnControls"
import "../components/keyPad"
import "../components/inputControls"
import "../components/messages"
import "../components/scoreDisplay"
import "../components/screens"
import "../components/dialogs"

Page {
  id: tournamentPage
  signal menuRequest

  function handleCloseEvent(event) {
    if (event.key === Qt.BackButton) {
      event.accepted = true
      Dialogs.openQuitDialog(menuRequest)
    }
  }

  function isPortrait() {
    return tournamentPage.height >= tournamentPage.width
  }

  function restartGame() {
    dialogLoader.sourceComponent = null
    dartsInitializer.reset()
    updateTurnValues()
    tournamentPage.forceActiveFocus()
  }

  function undo() {
    dartsTurns.undo()
    updateTurnValues()
    tournamentPage.forceActiveFocus()
  }

  function redo() {
    dartsTurns.redo()
    updateTurnValues()
  }

  function reportInputs() {
    if (privateData.inputs.length === 0)
      proceedDialog.visible = true
    else
      performReport()
  }

  function performReport() {
    const json = JSON.stringify(privateData.inputs)
    dartsInputs.add(json)
    updateTurnValues()
  }

  function updateTurnValues() {
    if (dartsPlayers.isWinnerFound()) {
      dialogLoader.sourceComponent = winnerScreen
      return
    }

    turnControls.update()
    messageSection.update()
    resetScoreDisplay()
  }

  function addInput(modId, point) {
    if (privateData.inputs.length > 2)
      return

    privateData.inputs.push({
                              "modId": modId,
                              "point": point
                            })

    const sum = inputsScore(privateData.inputs)
    scoreDisplay.updateScores(privateData.inputs, sum)
    scoreDisplay.subtract(sum)
  }

  function inputsScore(inputs) {
    let sum = 0
    let input = null
    for (var i = 0; i < inputs.length; i++) {
      input = inputs[i]
      sum += scoreValue(input.modId, input.point)
    }
    return sum
  }

  function scoreValue(modId, point) {
    if (modId === "T")
      return 3 * point
    else if (modId === "D")
      return 2 * point
    else
      return point
  }

  function popInput() {
    privateData.inputs.pop()
    const sum = inputsScore(privateData.inputs)
    scoreDisplay.subtract(sum)
    scoreDisplay.updateScores(privateData.inputs, sum)
  }

  function resetScoreDisplay() {
    privateData.inputs = []
    scoreDisplay.resetAndUpdate()
  }

  QtObject {
    id: privateData
    property var inputs: []
    property real width: isPortrait() ? parent.width : parent.width / 2
  }

  focus: true
  Keys.onPressed: event => handleCloseEvent(event)

  ConfirmDialog {
    id: restartDialog
    onAccepted: restartGame()
  }

  ConfirmDialog {
    id: proceedDialog
    onAccepted: performReport()
  }

  Component {
    id: winnerScreen

    WinnerScreen {
      anchors.fill: parent

      onRestartClicked: restartGame()
      onUndoClicked: undo()
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

  ScoreDisplay {
    id: scoreDisplay

    anchors.top: parent.top
    anchors.left: parent.left

    height: 146
    width: privateData.width

    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }

  MessagesDisplay {
    id: messageSection
    anchors.top: scoreDisplay.bottom
    anchors.left: parent.left
    width: privateData.width
    height: 48
  }

  TurnControls {
    id: turnControls
    anchors.top: messageSection.bottom
    anchors.left: parent.left
    width: privateData.width
    height: 48
    onUndoClicked: undo()
    onRedoClicked: redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls
    anchors.top: isPortrait() ? turnControls.bottom : parent.top
    anchors.right: parent.right
    width: privateData.width
    onPop: popInput()
    onFlush: resetScoreDisplay()
    height: 52
  }

  KeyPad {
    id: inputSection
    width: privateData.width
    anchors.top: inputControls.bottom
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    onEnter: (modId, point) => addInput(modId, point)
    onReport: reportInputs()
  }

  Loader {
    id: dialogLoader
    anchors.fill: parent
    asynchronous: true
    visible: status == Loader.Ready
  }

  Component.onCompleted: updateTurnValues()
  Component.onDestruction: dartsInitializer.saveState()
}
