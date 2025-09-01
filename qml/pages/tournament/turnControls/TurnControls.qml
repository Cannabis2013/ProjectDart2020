import QtQuick 6.0
import QtQuick.Controls 6.0

Item {
  id: turnRect

  signal undoClicked
  signal redoClicked
  signal restartClicked

  function update() {
    undoButton.active = dartsTurns.canUndo()
    redoButton.active = dartsTurns.canRedo()
  }

  Button {
    text: "Menu"
    anchors.left: parent.left
    height: parent.height
    anchors.margins: 6
    font.pointSize: 20
    onClicked: menuRequest()
  }

  Button {
    id: restartButton
    text: "Restart"
    font.pointSize: 20
    anchors.right: undoButton.left
    height: parent.height
    anchors.margins: 6
    onClicked: restartClicked()
  }

  ButtonControl {
    id: undoButton
    active: false
    width: 38
    anchors.right: redoButton.left
    height: parent.height
    anchors.margins: 6
    iconSource: "qrc:/pictures/Ressources/Pictures/undo.png"
    onButtonClicked: undoClicked()
  }

  ButtonControl {
    id: redoButton
    anchors.right: parent.right
    height: parent.height
    anchors.margins: 6
    active: false
    width: 38
    iconSource: "qrc:/pictures/Ressources/Pictures/redo.png"
    onButtonClicked: redoClicked()
  }
}
