import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts
import "../components"

Rectangle {
    id: playerDelegate

    signal clicked

    required property string name
    required property int index
    required property bool selected
    required property int placeIndex

    color: playerDelegate.selected ? Qt.rgba(24, 24, 24, .5) : Qt.rgba(24, 24, 24, .3)
    radius: 9
    height: 40
    width: ListView.view.width

    Text {
        id: delegateText
        anchors {fill: parent;margins: 9}
        color: "lightgray"
        font.pixelSize: 18
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: playerDelegate.name
    }
    MouseArea {
        anchors.fill: parent
        onClicked: playerDelegate.clicked()
    }
}
