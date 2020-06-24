import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    color: "transparent"

    clip: true

    GridLayout{
        id: componentLayout

        anchors.fill: parent

        flow: GridLayout.TopToBottom

        Layout.fillWidth: true
        Layout.fillHeight: true

        Layout.alignment: Qt.AlignHCenter
        CustomTableComponent{
            id: scoreTable

            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true
            Layout.minimumHeight: scoreTable.calcContentHeight() + 30

            Component.onCompleted: {
                scoreTable.appendHeader("Martin",0x2);
                scoreTable.appendHeader("Kent",0x2);
                scoreTable.appendHeader("Ole",0x2);

                scoreTable.addData(0,0,4);
                scoreTable.addData(1,0,24);
                scoreTable.addData(2,0,33);
            }
        }

        Rectangle{
            Layout.fillHeight: true
        }
    }
}
