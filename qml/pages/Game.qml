pragma ComponentBehavior: Bound
import QtQuick 2.1
import QtQuick.Controls 6.0
import "../components"

Page {
  id: tournamentPage


  signal menuRequest

  focus: true

  function handleCloseEvent(event) {
    if (event.key === Qt.BackButton) {
      event.accepted = true;
      menuRequest();
    }
  }

  function isPortrait() {
    return tournamentPage.height >= tournamentPage.width;
  }

  function restartGame() {
    restartDialog.visible = false;
    dartsInitializer.reset();
    updateTurnValues();
    tournamentPage.forceActiveFocus();
  }

  function undo() {
    dartsTurns.undo();
    updateTurnValues();
    tournamentPage.forceActiveFocus();
  }

  function redo() {
    dartsTurns.redo();
    updateTurnValues();
  }

  function reportInputs() {
    if (privateData.inputs.length === 0)
      proceedDialog.visible = true;
    else
      performReport();
  }

  function performReport() {
    const json = JSON.stringify(privateData.inputs);
    dartsInputs.add(json);
    updateTurnValues();
  }

  function updateTurnValues() {
    if (winnerInfo.isWinnerFound()) {
      dialogLoader.sourceComponent = winnerScreen;
      return;
    }
    updateMessageComponent();
    turnControls.update();
    resetScoreDisplay();
  }

  function addInput(modId, point) {
    if (privateData.inputs.length > 2)
      return;
    privateData.inputs.push({
      "modId": modId,
      "point": point
    });

    const sum = totalInputScore(privateData.inputs);
    infoDisplay.updateScores(privateData.inputs, sum);
    updateMessageComponent();
    infoDisplay.subtract(sum);
  }

  function updateMessageComponent() {
    const count = privateData.inputs.length;
    const turnIndex = count > 0 ? count : 0;
    const sum = totalInputScore(privateData.inputs);
    const remaining = dartsScores.current() - sum;
    const row = dartsFinishes.finish(remaining, turnIndex);
    messageSection.update(row);
  }

  function totalInputScore(inputs) {
    let sum = 0;
    let input = null;
    for (var i = 0; i < inputs.length; i++) {
      input = inputs[i];
      sum += scoreValue(input.modId, input.point);
    }
    return sum;
  }

  function scoreValue(modId, point) {
    if (modId === "T")
      return 3 * point;
    else if (modId === "D")
      return 2 * point;
    else
      return point;
  }

  function popInput() {
    privateData.inputs.pop();
    const sum = totalInputScore(privateData.inputs);
    infoDisplay.subtract(sum);
    infoDisplay.updateScores(privateData.inputs, sum);
    updateMessageComponent();
  }

  function resetScoreDisplay() {
    privateData.inputs = [];
    infoDisplay.resetAndUpdate();
    updateMessageComponent();
  }

  QtObject {
    id: privateData
    property var inputs: []
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
      onMenuRequest: tournamentPage.menuRequest()
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

    height: 256
    width: tournamentPage.isPortrait() ? tournamentPage.width : tournamentPage.width / 2

    onOpenPlayerInfoDialog: dialogLoader.sourceComponent = playersInfoScreen
  }

  MessagesDisplay {
    id: messageSection

    anchors.left: parent.left
    anchors.top: infoDisplay.bottom
    anchors.bottom: tournamentPage.isPortrait() ? turnControls.top : parent.bottom
    anchors.margins: 8

    width: tournamentPage.isPortrait() ? parent.width : parent.width / 2
    height: 64
  }

  TurnControls {
    id: turnControls

    anchors.bottom: keypad.top
    anchors.left: keypad.left
    anchors.margins: 8

    onUndoClicked: tournamentPage.undo()
    onRedoClicked: tournamentPage.redo()
    onRestartClicked: restartDialog.visible = true
  }

  InputControls {
    id: inputControls

    anchors.bottom: keypad.top
    anchors.right: keypad.right
    anchors.margins: 8

    onPop: tournamentPage.popInput()
    onFlush: tournamentPage.resetScoreDisplay()
    onMiss: tournamentPage.addInput("S", 0)
  }

  KeyPad {
    id: keypad

    width: tournamentPage.isPortrait() ? tournamentPage.width : tournamentPage.width / 2
    height: tournamentPage.isPortrait() ? 360 : parent.height - 40

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
