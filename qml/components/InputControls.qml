import QtQuick 6.0

Item {
  id: inputControls

  signal pop
  signal flush
  signal miss

  PushButton {
    id: flushButton

    onClicked: inputControls.flush()

    height: 48
    width: 80
    anchors{
      right: popButton.left
      verticalCenter: parent.verticalCenter
      rightMargin: 4
    }
    label: "Flush"
    labelSize: 24
  }

  PushButton {
    id: popButton

    onClicked: inputControls.pop()

    height: 48
    width: 80
    anchors{
      horizontalCenter: parent.horizontalCenter
      verticalCenter: parent.verticalCenter
      leftMargin: 4
    }
    label: "Pop"
    labelSize: 24
  }

  PushButton {
    id: missButton

    onClicked: inputControls.miss()

    height: 48
    width: 80
    anchors{
      left: popButton.right
      verticalCenter: parent.verticalCenter
      leftMargin: 4
    }
    label: "Miss"
    labelSize: 24
  }
}
