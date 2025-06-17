import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Item {
    id: inputDelegate
    clip: true

    Image {
        id: arrowImage
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        width: 32
        source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
    }

    Text {
        id: roundText
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: arrowImage.right
        anchors.leftMargin: 6
        width: 20
        text: round
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
    }

    Text {
        text: value
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: roundText.right
        anchors.leftMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 8
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pointSize: 20
        font.weight: Font.Bold
    }
}
