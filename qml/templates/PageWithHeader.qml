import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Page {
  id: pageRect

  signal backClicked
  signal backLongClicked

  anchors.fill: parent

  focus: true

  property string buttonText: "Back"
  onButtonTextChanged: pageButton.text = buttonText

  property string pageTitle: ""
  onPageTitleChanged: pageLabel.text = pageTitle

  header: Item {
    id: headerRect

    height: 48

    Button {
      id: pageButton

      anchors.margins: 8
      anchors.left: parent.left
      anchors.verticalCenter: parent.verticalCenter

      font.pointSize: 16
      font.weight: Font.Bold

      text: pageRect.buttonText

      height: 40

      onClicked: pageRect.backClicked()
      onPressAndHold: pageRect.backLongClicked()
    }

    Text {
      id: pageLabel

      height: 32

      anchors.verticalCenter: parent.verticalCenter
      anchors.left: pageButton.right
      anchors.leftMargin: 8
      anchors.right: parent.right

      font.pointSize: 16

      color: "white"

      verticalAlignment: Text.AlignVCenter
    }
  }
}
