pragma ComponentBehavior: Bound
import QtQuick 6.0
import QtQuick.Controls
import "../components"

Page {
  id: scoreCalculator
  signal backClicked

  header: PageHeader {
    pageTitle: "Afslutnings udregner"
    onBack: scoreCalculator.backClicked()
  }

  function appendDigit(digit) {
    let digits = remainingText.text;
    const numberOfDigits = digits.length;
    if (numberOfDigits >= 3)
      return;

    digits += parseInt(digit);

    if (numberOfDigits === 0 && digit === 0)
      return;
    if (parseInt(digits) > 180)
      return;

    remainingText.text = digits;
    variables.remaining = parseInt(digits)
  }

  function popDigit() {
    const digits = remainingText.text;

    const index = digits.length - 1;
    if (index < 0)
      return

    const slicedDigits = digits.slice(0, index)
    variables.remaining = slicedDigits !== "" ? parseInt(slicedDigits) : -1
  }

  function clearDigits() {
    variables.remaining = -1
  }

  function appendInput(point, mod) {
    if (variables.turnIndex >= 3)
      return
    else if(variables.remaining === -1)
      return

    variables.turnIndex++

    const inputAsString = `${mod}${point}`;
    const input = {"mod": mod,"point" : point}
    variables.inputs.push(input)

    variables.remaining -= scoreCalculator.calculateScore(mod,point)
  }

  function updateViews(){
    const remaining = variables.remaining
    if(remaining == -1)
      remainingText.text = ""
    else if(remaining == 0)
      remainingText.text = "Congratulations"
    else
      remainingText.text = remaining

    let input = null;
    let str = "";
    const length = variables.inputs.length;
    for (let i = 0; i < length; i++) {
      input = variables.inputs[i];
      str += `${input.mod}${input.point}`;
      str += i < length - 1 ? ' ' : '';
    }

    inputsText.text = str

    const turnIndex = variables.turnIndex
    finishRowText.text = dartsFinishes.finish(remaining, turnIndex)
  }

  function popInput(){
    if(variables.turnIndex <= 0)
      return

    const poppedInput = variables.inputs.pop()

    variables.remaining += scoreCalculator.calculateScore(poppedInput.mod,poppedInput.point)

    variables.turnIndex--
  }

  function calculateScore(mod, point){
    let modValue = 1
    if(mod == "T")
      modValue = 3
    else if(mod == "D")
      modValue = 2

    return modValue * point
  }

  function reset() {
    variables.remaining = -1
    variables.turnIndex = 0
    variables.inputs = []
  }

  QtObject {
    id: variables
    property int remaining: -1
    onRemainingChanged: inputButton.enabled = remaining !== -1
    property int turnIndex: 0
    property var inputs: []
  }

  padding: 9

  Rectangle {
    height: 128
    width: parent.width

    color: "#4f4f4f"

    Text {
      id: remainingText

      anchors.topMargin: 9
      anchors.top: parent.top

      height: 24
      width: parent.width

      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter

      font.pixelSize: 32
      color: "lightgray"
    }

    Text {
      id: inputsText

      anchors.top: remainingText.bottom
      anchors.bottomMargin: 9

      height: 48
      width: parent.width

      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter

      font.pixelSize: 24
      color: "lightgray"
    }

    Text {
      id: finishRowText

      anchors.top: inputsText.bottom
      anchors.bottom: parent.bottom
      width: parent.width

      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter

      font.pixelSize: 40
      color: "lightgray"
    }
  }

  PushButton {
    id: resetButton
    width: 64
    anchors.bottom: keyPadLoader.top
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.margins: 9

    label: "Reset"

    onClicked: {
      scoreCalculator.reset();
      scoreCalculator.updateViews()
      keyPadLoader.sourceComponent = numberKeyPad;
    }
  }

  PushButton {
    id: scoreButton

    width: 128

    anchors.left: parent.left
    anchors.bottom: keyPadLoader.top
    anchors.margins: 9

    label: "Enter score"

    onClicked: keyPadLoader.sourceComponent = numberKeyPad
  }

  PushButton{
    id: popInputButton

    width: 96

    label: "Pop input"
    anchors.right: parent.right
    anchors.bottom: inputButton.top
    anchors.margins: 9

    onClicked: {
      scoreCalculator.popInput()
      scoreCalculator.updateViews()
    }
  }

  PushButton {
    id: inputButton

    width: 128

    anchors.right: parent.right
    anchors.bottom: keyPadLoader.top
    anchors.margins: 9

    enabled: false

    label: "Enter inputs"

    onClicked: keyPadLoader.sourceComponent = inputKeyPad
  }

  Component {
    id: numberKeyPad
    NumberKeyPad {
      onEnter: value => {
        scoreCalculator.appendDigit(value)
        scoreCalculator.updateViews()
      }

      onPop: {
        scoreCalculator.popDigit();
        scoreCalculator.updateViews()
      }

      onClear: {
        scoreCalculator.clearDigits()
        scoreCalculator.updateViews()
      }
    }
  }

  Component {
    id: inputKeyPad
    KeyPad {
      anchors.fill: parent

      width: parent.width
      height: 224

      onEnter: (mod, point) => {
        scoreCalculator.appendInput(point, mod)
        scoreCalculator.updateViews()
      }
    }
  }

  Loader {
    id: keyPadLoader
    sourceComponent: numberKeyPad

    anchors.bottom: parent.bottom

    width: parent.width
    height: 256
  }
}
