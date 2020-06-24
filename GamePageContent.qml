import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    color: "transparent"

    GridLayout{
        id: componentLayout

        anchors.fill: parent


        flow: GridLayout.TopToBottom

        CustomTableComponent{
            id: scoreTable

            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.alignment: Qt.AlignHCenter

            verticalHeaderFillMode: 0x1

            Component.onCompleted: {
                scoreTable.appendHeader("Martin",0x2);
                scoreTable.appendHeader("Kent",0x2);
                scoreTable.appendHeader("Ole",0x2);

                scoreTable.addData(0,0,4);
                scoreTable.addData(1,0,24);
                scoreTable.addData(2,0,33);
            }
        }
    }
}
