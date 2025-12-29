import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  signal enter(int value)
  signal pop()
  signal clear()

  GridLayout {
    id: numberPads
    width: parent.width
    height: parent.height
    columns: 3
    columnSpacing: 1
    rowSpacing: 1
    layoutDirection: Qt.RightToLeft

    Repeater {
      id: repeater
      model: 9

      Pad {
        text: `${9 - index}`

        color: "white"

        onReleased: enter(9 - index)
      }
    }

    Pad{
      text:"0"
      Layout.columnSpan: 3

      color: "white"
      onReleased: enter(0)
    }
  }
}
