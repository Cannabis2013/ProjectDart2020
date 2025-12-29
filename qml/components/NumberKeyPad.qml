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
    columnSpacing: 0
    rowSpacing: 0
    layoutDirection: Qt.RightToLeft

    Repeater {
      model: 9

      Pad {
        text: `${9 - index}`

        color: "white"

        onReleased: enter(9 - index)
      }
    }

    Pad{
      text:"Flush"

      color: "white"

      onReleased: clear()
    }

    Pad{
      text:"0"

      color: "white"
      onReleased: enter(0)
    }

    Pad{
      text: "Pop"

      color: "white"

      onReleased: pop()
    }
  }
}
