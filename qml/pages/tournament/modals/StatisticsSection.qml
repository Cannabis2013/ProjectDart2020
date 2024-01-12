import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../turn"
import "../keyPad"

Item {
        Column {
                anchors.fill: parent

                Text {
                        id: statisticsSectionTitle
                        height: 64
                        width: parent.width
                        font.pointSize: 48
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        text: qsTr("Statistics")
                }

                Text {
                        text: "Peter Wright"
                        color: "white"
                        height: 32
                        width: parent.width
                }

                Text {
                        text: "Van Gerwin"
                        color: "white"
                        height: 32
                        width: parent.width
                }
        }
}
