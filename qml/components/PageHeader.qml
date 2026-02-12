import QtQuick 6.0

Item {
    id: headerRect

    signal back

    property string buttonLabel: "Back"
    onButtonLabelChanged: pageButton.label = buttonLabel
    property string pageTitle: ""
    onPageTitleChanged: pageLabel.text = pageTitle

    height: 64

    PushButton {
        id: pageButton

        onClicked: headerRect.back()

        height: 48
        width: 64
        anchors{
          left: parent.left
          verticalCenter: parent.verticalCenter
          margins: 8
        }
        label: headerRect.buttonLabel
    }
    Text {
        id: pageLabel

        height: 48
        anchors{
          right: parent.right
          left: pageButton.right
          verticalCenter: parent.verticalCenter
          leftMargin: 16
        }
        font.pixelSize: 20
        color: "lightgray"
        verticalAlignment: Text.AlignVCenter
    }
}
