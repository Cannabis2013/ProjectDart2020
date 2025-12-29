import QtQuick 6.0

Item {
    id: headerRect

    focus: true

    signal back

    property string buttonLabel: "Back"
    onButtonLabelChanged: pageButton.label = buttonLabel

    property string pageTitle: ""
    onPageTitleChanged: pageLabel.text = pageTitle

    height: 48

    PushButton {
        id: pageButton
        anchors.margins: 8
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        label: headerRect.buttonLabel
        height: 32
        width: 64
        onClicked: headerRect.back()
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
