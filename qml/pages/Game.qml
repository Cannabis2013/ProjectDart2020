import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../components"

pragma ComponentBehavior: Bound

Page {
  id: tournamentPage

  signal menuRequest

  header: PageHeader{
    buttonLabel: "Menu"
    height: 40
    onBack: tournamentPage.menuRequest()
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
    updateMessageComponent()
    turnControls.update()
    resetScoreDisplay()
  }

  function addInput(modId, point) {
    if (privateData.inputs.length > 2)
      return

    privateData.inputs.push({
                              "modId": modId,
                              "point": point
                            })

    const sum = totalInputScore(privateData.inputs)
    infoDisplay.updateScores(privateData.inputs, sum)
    updateMessageComponent()
    infoDisplay.subtract(sum)
  }

  function updateMessageComponent(){
    const count = privateData.inputs.length
    const turnIndex = count > 0 ? count : 0
    const sum = totalInputScore(privateData.inputs)
    const remaining = dartsScores.current() - sum
    const row = dartsFinishes.finish(remaining,turnIndex)
    messageSection.update(row)
  }

  function totalInputScore(inputs) {
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
    const sum = totalInputScore(privateData.inputs)
    infoDisplay.subtract(sum)
    infoDisplay.updateScores(privateData.inputs, sum)
    updateMessageComponent()
  }

  function resetScoreDisplay() {
    privateData.inputs = []
    infoDisplay.resetAndUpdate()
    updateMessageComponent()
  }

  QtObject {
    id: privateData
    property var inputs: []
    property real width: tournamentPage.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
  }

  Keys.onPressed: event => handleCloseEvent(event)

  ConfirmDialog {
    id: restartDialog
    onAccepted: tournamentPage.restartGame()
  }

  ConfirmDialog {
    id: proceedDialog
    onAccepted: tournamentPage.performReport()
  }

  Component {
    id: winnerScreen

    WinnerScreen {
      anchors.fill: parent
      onRestartClicked: tournamentPage.restartGame()
      onUndoClicked: tournamentPage.undo()
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

    anchors.top: tournamentPage.isPortrait() ? messageSection.bottom : parent.top
    anchors.left: keypad.left
    anchors.leftMargin: 8
    onUndoClicked: tournamentPage.undo()
    onRedoClicked: tournamentPage.redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls
    anchors.top: tournamentPage.isPortrait() ? messageSection.bottom : parent.top
    anchors.right: keypad.right
    anchors.rightMargin: 8
    onPop: tournamentPage.popInput()
    onFlush: tournamentPage.resetScoreDisplay()
  }

  KeyPad {
    id: keypad
    width: privateData.width
    anchors.topMargin: 8
    anchors.top: inputControls.bottom
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    onEnter: (modId, point) => tournamentPage.addInput(modId, point)
    onReport: tournamentPage.reportInputs()
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
