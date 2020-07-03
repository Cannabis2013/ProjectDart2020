import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.maximumWidth: defaultPageContentWidth

    Layout.alignment: Qt.AlignHCenter

    color: "transparent"

    clip: true

    GridLayout{
        id: componentLayout

        anchors.fill: parent

        columns: 1

        flow: GridLayout.TopToBottom

        TurnNavigationComponent{
            id: turnNavigator
            Layout.fillWidth: true
            height: 64

            Layout.alignment: Qt.AlignHCenter
        }

        CustomTable{
            id: scoreTable

            color: "transparent"

            verticalHeaderFillMode: 0x1
            Layout.fillWidth: true

            height: 125
        }

        Rectangle{
            Layout.minimumHeight: 25
            Layout.maximumHeight: 25
        }

        KeyPadComponent{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.minimumHeight: 128
            Layout.maximumHeight: 384

            Layout.alignment: Qt.AlignTop
        }
        Rectangle{
            Layout.fillHeight: true
        }
    }
    Component.onCompleted: {
        scoreTable.appendHeader("Martin",0x2);
        scoreTable.appendHeader("Kent KillerHertz",0x2);
        scoreTable.appendHeader("Nikolaj Pedersen",0x2);
        scoreTable.appendHeader("Ole",0x2);
        scoreTable.appendHeader("Per",0x2);

        for(var r = 0;r < 5; r++)
        {
            for(var c = 0;c < 30; c++)
            {
                scoreTable.addData(r,c,501);
            }
        }

    }
}
