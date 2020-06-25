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

        DecoratedButtonComponent{
            width: 50
            height: 50
        }

        CustomTableComponent{
            id: scoreTable

            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true
            Layout.minimumHeight: scoreTable.calcContentHeight() + 30

            Component.onCompleted: {
                scoreTable.appendHeader("Martin",0x2);
                scoreTable.appendHeader("Kent KillerHertz",0x2);
                scoreTable.appendHeader("Ole",0x2);

                scoreTable.addData(0,0,4);
                scoreTable.addData(1,0,24);
                scoreTable.addData(2,0,33);
                scoreTable.addData(0,1,12);
                scoreTable.addData(1,1,11);
                scoreTable.addData(2,1,50);
            }
        }

        Rectangle{
            Layout.fillHeight: true
        }
    }
}
