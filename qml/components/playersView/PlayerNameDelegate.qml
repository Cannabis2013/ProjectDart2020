import QtQuick 2.15
import "../../components/buttons"

Component {
        id: viewDelegate
        Row {
                Rectangle {
                        width: 256
                        height: 64
                        clip: true
                        radius: 12
                        color: "grey"
                        Text {
                                anchors.fill: parent
                                text: name
                                font.pointSize: 20
                                color: "white"
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                        }
                        NewPushButton {
                                x: 231
                                y: 5
                                width: 20
                                height: 20
                                text: "X"
                                radius: 24
                                backgroundColor: "red"
                                onClicked: playersModel.remove(index)
                        }
                }
        }
}
