import QtQuick 6.0
import QtQuick.Controls 6.0

Item {
  id: turnRect

  signal undoClicked
  signal redoClicked
  signal restartClicked

  function update() {
    undoButton.visible = dartsTurns.canUndo()
    redoButton.visible = dartsTurns.canRedo()
  }

  Button {
    text: "Menu"

    anchors.left: parent.left
    anchors.margins: 6

    height: parent.height

    font.pointSize: 20

    onClicked: menuRequest()
  }

  Button {
    id: restartButton

    anchors.right: undoButton.left
    anchors.rightMargin: 6

    height: parent.height

    text: "Restart"

    font.pointSize: 20

    onClicked: restartClicked()
  }

  Item{
    id: undoButton

    width: parent.height
    height: parent.height

    anchors.right: redoButton.left
    anchors.rightMargin: 8

    Image {
      anchors.centerIn: parent

      width: parent.height
      height: parent.height

      source: "qrc:/pictures/Ressources/Pictures/undo.png"
    }

    MouseArea {
      id: undoMouseArea

      anchors.fill: parent

      onClicked: undoClicked()
    }
  }

  Item{
    id: redoButton

    width: parent.height
    height: parent.height

    anchors.right: parent.right
    visible: false

    Image {
      anchors.centerIn: parent

      width: parent.height
      height: parent.height

      source: "qrc:/pictures/Ressources/Pictures/redo.png"
    }

    MouseArea {
      id: redoMouseArea

      anchors.fill: parent

      onClicked: redoClicked()
    }
  }
}
