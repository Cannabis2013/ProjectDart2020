import QtQuick 2.0
import QtQuick.Layouts 1.3
import "playersSection.js" as Scripts

Rectangle {
        color: "green"

        function move(pos) {
                handle.x = pos
        }

        readonly property int handleWidth: handle.width

        Image {
                id: handle

                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -3

                height: 24
                width: 24

                Behavior on x {
                        NumberAnimation {
                                duration: 400
                                easing.type: Easing.OutBounce
                                easing.amplitude: 1
                        }
                }

                source: "qrc:/pictures/Ressources/Pictures/up_arrow.png"
        }
}
