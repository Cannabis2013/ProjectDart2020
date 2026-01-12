import QtQuick 6.0

Item {
  id: turnControls

  signal undoClicked
  signal redoClicked
  signal restartClicked

  height: 32
  width: 73

  function update() {
    undoButton.opacity = dartsTurns.canUndo() ? 1 : .1;
    redoButton.opacity = dartsTurns.canRedo() ? 1 : .1;
  }

  Item {
    id: undoButton
    width: parent.height
    height: parent.height
    anchors.left: parent.left
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

  Item {
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
