pragma ComponentBehavior: Bound
import QtQuick 6.0
import QtQuick.Controls
import "../components"

Page {
  id: scoreCalculator

  signal backClicked

  header: PageHeader {
    onBack: scoreCalculator.backClicked()
  }

  function appendDigit(digit) {
    let digits = variables.remaining

    digits = digits*10 + digit

    if (digits > 501)
      return;

    variables.remaining = digits

    if(digits * 10 > 501){
      keyPadLoader.sourceComponent = inputKeyPad
      return
    }
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
    variables.remaining = 0
  }

  function appendInput(point, mod) {
    if (variables.turnIndex >= 3 || variables.remaining === 0)
      return

    const remaining = variables.remaining - scoreCalculator.calculateScore(mod,point)
    if(remaining < 0)
      return

    variables.turnIndex++

    const inputAsString = `${mod}${point}`;
    const input = {"mod": mod,"point" : point}
    variables.inputs.push(input)

    variables.remaining = remaining
  }

  function updateViews(){
    const remaining = variables.remaining

    remainingText.text = remaining != 0 ? remaining : ""

    let input = null
    let str = ""
    const length = variables.inputs.length;
    for (let i = 0; i < length; i++) {
      input = variables.inputs[i]
      str += `${input.mod}${input.point}`
      str += i < length - 1 ? ' ' : ''
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
    if(mod === "T")
      modValue = 3
    else if(mod === "D")
      modValue = 2

    return modValue * point
  }

  function reset() {
    variables.remaining = 0
    variables.turnIndex = 0
    variables.inputs = []
  }

  QtObject {
    id: variables
    property int remaining: 0
    onRemainingChanged: {
      const isEnterDigitState = remaining !== 0 && turnIndex == 0
      inputButton.enabled = isEnterDigitState
      popDigitButton.enabled = isEnterDigitState
      scoreButton.enabled = isEnterDigitState
      flushDigitButton.enabled = isEnterDigitState

      if(remaining == 0)
        keyPadLoader.sourceComponent = numberKeyPad
    }

    property int turnIndex: 0
    onTurnIndexChanged: popInputButton.enabled = turnIndex > 0

    property var inputs: []
  }

  Rectangle {
    height: 128
    width: parent.width

    color: "#2f2f2f"

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
    id: popDigitButton

    width: 128

    anchors.left: parent.left
    anchors.bottom: flushDigitButton.top
    anchors.margins: 9

    label: "Pop digit"

    enabled: false

    onClicked: {
      scoreCalculator.popDigit()
      scoreCalculator.updateViews()
    }
  }

  PushButton {
    id: flushDigitButton

    width: 128

    anchors.left: parent.left
    anchors.bottom: scoreButton.top
    anchors.margins: 9

    label: "Flush digits"

    enabled: false

    onClicked: {
      scoreCalculator.clearDigits()
      scoreCalculator.updateViews()
    }
  }

  PushButton {
    id: scoreButton

    width: 128

    anchors.left: parent.left
    anchors.bottom: keyPadLoader.top
    anchors.margins: 9

    label: "Scorepad"

    onClicked: keyPadLoader.sourceComponent = numberKeyPad
  }

  PushButton{
    id: popInputButton

    width: 96

    label: "Pop input"
    anchors.right: parent.right
    anchors.bottom: inputButton.top
    anchors.margins: 9

    enabled: false

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

    label: "Inputpad"

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
        scoreCalculator.popDigit()
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
