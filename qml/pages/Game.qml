import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../components"

Page {
  id: tournamentPage
  signal menuRequest

  header: PageHeader{
    buttonLabel: "Menu"
    height: 40
    onBack: menuRequest()
  }

  focus: true

  function handleCloseEvent(event) {
    if (event.key === Qt.BackButton) {
      event.accepted = true
      menuRequest()
    }
  }

  function isPortrait() {
    return tournamentPage.height >= tournamentPage.width
  }

  function restartGame() {
    restartDialog.visible = false
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
    infoDisplay.updateScores(privateData.inputs, sum)
    infoDisplay.subtract(sum)
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
    infoDisplay.subtract(sum)
    infoDisplay.updateScores(privateData.inputs, sum)
  }

  function resetScoreDisplay() {
    privateData.inputs = []
    infoDisplay.resetAndUpdate()
  }

  QtObject {
    id: privateData
    property var inputs: []
    property real width: isPortrait() ? parent.width : parent.width / 2
  }

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

  InfoDisplay {
    id: infoDisplay
    anchors.top: parent.top
    anchors.left: parent.left
    height: 146
    width: privateData.width
    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }

  MessagesDisplay {
    id: messageSection
    anchors.top: infoDisplay.bottom
    anchors.left: parent.left
    width: 96
  }

  TurnControls {
    id: turnControls

    anchors.top: isPortrait() ? messageSection.bottom : parent.top
    anchors.left: keypad.left
    anchors.leftMargin: 8
    onUndoClicked: undo()
    onRedoClicked: redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls
    anchors.top: isPortrait() ? messageSection.bottom : parent.top
    anchors.right: keypad.right
    anchors.rightMargin: 8
    onPop: popInput()
    onFlush: resetScoreDisplay()
  }

  KeyPad {
    id: keypad
    width: privateData.width
    anchors.topMargin: 8
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
