import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        anchors.fill: parent

        function setVisibleDarts(number) {
                const children = dartsLayout.children
                for (var i = children.length - 1; i >= 0; i--) {
                        const child = children[i]
                        child.visible = i >= number
                }
        }

        Row {
                id: dartsLayout
                layoutDirection: Qt.RightToLeft

                move: Transition {
                        NumberAnimation {
                                properties: "x,y"
                                duration: 250
                        }
                }

                populate: Transition {
                        NumberAnimation {
                                properties: "x,y"
                                duration: 350
                        }
                }

                x: 6
                y: 6
                width: 38
                height: 40
                spacing: 4

                NumberAnimation on scale {
                        from: 0.0
                        to: 1
                        duration: 175
                }

                ArrowImage {}
                ArrowImage {}
                ArrowImage {}
        }
}
