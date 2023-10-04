import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        // Text content
        readonly property string iconText: initialsText.text
        signal setIconInitials(string name)
        onSetIconInitials: initialsText.text = name[0]

        // Geometry
        radius: 24
        width: 40
        height: 40

        Text {
                id: initialsText
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("MH")
        }
}
