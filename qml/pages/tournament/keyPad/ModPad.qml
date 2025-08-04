import QtQuick 6.0
import QtQuick.Layouts 1.3

Pad {
  property string modId: ""
  property bool selected: false
  onSelectedChanged: scale = selected ? 0.9 : 1

  color: "lightgreen"

  signal modClicked(string modId)

  onClicked: {
    selected = !selected
    scale = selected ? 0.9 : 1
    modClicked(modId)
  }
}
