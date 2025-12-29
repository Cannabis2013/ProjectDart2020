import QtQuick 6.0
import QtQuick.Layouts 1.3


Item {
  id: keyPad

  function handleNumberPadClick(point) {
    let modId
    if (modTripple.selected)
      modId = modTripple.text
    else if (modDouble.selected)
      modId = modDouble.text
    else
      modId = "S"

    enter(modId, point)
    unSelectMods()
  }

  function handleSpecialPadClick(point) {
    enter("S", point)
    unSelectMods()
  }

  function unSelectMods() {
    modTripple.selected = false
    modDouble.selected = false
  }

  function selectMod(modId) {
    (modId === "T" ? modDouble : modTripple).selected = false
  }

  signal report
  signal enter(string mod, int point)

  GridLayout {
    id: numberPads
    width: parent.width * 0.8
    height: parent.height
    columns: 4
    columnSpacing: 1
    rowSpacing: 1
    layoutDirection: Qt.RightToLeft

    Repeater {
      model: 20

      Pad {
        text: `${20 - index}`

        color: "white"

        onReleased: keyPad.handleNumberPadClick(20 - index)
      }
    }
  }

  ColumnLayout {
    id: specialPads
    spacing: 1
    anchors.left: numberPads.right
    width: parent.width * 0.2
    height: parent.height

    Pad {
      id: modTripple

      property bool selected: false
      onSelectedChanged: scale = selected ? 0.9 : 1

      color: "lightgreen"

      text: "T"

      onClicked: {
        selected = !selected
        scale = selected ? 0.9 : 1
        keyPad.selectMod("T")
      }
    }

    Pad {
      id: modDouble

      property string modId: ""
      property bool selected: false

      text: "D"

      onSelectedChanged: scale = selected ? 0.9 : 1

      color: "lightgreen"

      signal modClicked(string modId)

      onClicked: {
        selected = !selected
        scale = selected ? 0.9 : 1
        keyPad.selectMod("D")
      }
    }

    Pad {
      color: "red"

      text: "50"

      onReleased: keyPad.handleSpecialPadClick(50)
    }

    Pad {
      color: "green"

      text: "25"

      onReleased: keyPad.handleSpecialPadClick(25)
    }

    Pad {
      color: "orange"
      onReleased: keyPad.report()
      image: "qrc:/pictures/Ressources/Pictures/upArrow.png"
    }
  }
}
