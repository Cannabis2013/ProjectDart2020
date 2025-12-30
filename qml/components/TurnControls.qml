import QtQuick 6.0
import QtQuick.Controls 6.0

Item {
  id: turnControls

  signal undoClicked
  signal redoClicked
  signal restartClicked

  height: 32
  width: 165

  function update() {
    undoButton.opacity = dartsTurns.canUndo() ? 1 : .1
    redoButton.opacity = dartsTurns.canRedo() ? 1 : .1
  }

  PushButton {
    id: restartButton

    anchors.left: parent.left

    width: 96
    height: parent.height

    label: "Restart"
    labelSize: 24

    onClicked: turnControls.restartClicked()
  }

  Item{
    id: undoButton
    width: parent.height
    height: parent.height
    anchors.left: restartButton.right
    anchors.leftMargin: 8

    Image {
      anchors.fill: parent
      source: "qrc:/pictures/Ressources/Pictures/undo.png"
    }

    MouseArea {
      id: undoMouseArea
      anchors.fill: parent
      onClicked: turnControls.undoClicked()
    }
  }

  Item{
    id: redoButton

    width: parent.height
    height: parent.height
    anchors.left: undoButton.right
    anchors.leftMargin: 8

    Image {
      anchors.fill: parent
      source: "qrc:/pictures/Ressources/Pictures/redo.png"
    }

    MouseArea {
      id: redoMouseArea
      anchors.fill: parent
      onClicked: turnControls.redoClicked()
    }
  }
}
