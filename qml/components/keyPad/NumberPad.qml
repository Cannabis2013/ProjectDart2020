import QtQuick 6.0
import QtQuick.Layouts 1.3

Pad {
  id: numberPadRect

  property int padValue: -1

  color: "white"

  signal padClicked(int value)

  onReleased: {
    numberPadRect.padClicked(numberPadRect.padValue)
  }
}
