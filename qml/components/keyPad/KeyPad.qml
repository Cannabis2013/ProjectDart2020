import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "keyPad.js" as Scripts

Item {
  signal report
  signal enter(string modId, int point)

  GridLayout {
    id: numberPads
    width: parent.width * 0.8
    height: parent.height
    columns: 4
    columnSpacing: 0
    rowSpacing: 0
    layoutDirection: Qt.RightToLeft

    Repeater {
      model: 20

      NumberPad {
        padValue: 20 - index
        text: `${20 - index}`
        onPadClicked: padValue => Scripts.handleNumberPadClick(padValue)
      }
    }
  }

  ColumnLayout {
    id: specialPads
    spacing: 0
    anchors.left: numberPads.right
    width: parent.width * 0.2
    height: parent.height

    ModPad {
      id: modTripple
      text: "T"
      onModClicked: modId => Scripts.selectTrippeMod(modId)
    }

    ModPad {
      id: modDouble
      text: "D"
      onModClicked: modId => Scripts.selectDoubleMod(modId)
    }

    NumberPad {
      color: "red"
      padValue: 50
      text: "50"
      onPadClicked: value => Scripts.handleSpecialPadClick(padValue)
    }

    NumberPad {
      text: "25"
      color: "green"
      padValue: 25
      onPadClicked: value => Scripts.handleSpecialPadClick(padValue)
    }

    Pad {
      color: "orange"
      onReleased: report()
      image: "qrc:/pictures/Ressources/Pictures/upArrow.png"
    }
  }
}
