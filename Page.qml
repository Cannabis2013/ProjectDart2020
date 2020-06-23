import QtQuick 2.0

import QtQuick.Layouts 1.3

Rectangle {

    id: pageBody
    color: "#A54141"

    signal backButtonPressed

    property Item content: Item{}
    onContentChanged: {
        pageLayout.children[2] = content;
    }
    property string pageTitle: "Page title"
    onPageTitleChanged: pageTitleComponent.text = pageTitle

    GridLayout{
        id: pageLayout
        anchors.fill: parent

        rowSpacing: 10

        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 5

        flow: GridLayout.TopToBottom

        GridLayout{

            Layout.fillWidth: true
            Layout.fillHeight: true

            columns: 2
            rows: 1

            flow: GridLayout.LeftToRight

            PushButton
            {
                width: 65
                height: 30

                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft

                textColor: "white"

                text: "Back"

                fontSize: 10

                onClicked: backButtonPressed()
            }

            MyLabel{

                id: pageTitleComponent
                Layout.fillWidth: true
                fontSize: 20
                textLeftMargin: 10

                Layout.maximumHeight: 30

                text: pageBody.pageTitle
            }
        }

        MyRectangle
        {
            id: upperLayoutSpacer

            topBorderWidth: 1

            Layout.fillWidth: true

            Layout.alignment: Qt.AlignTop

            height: 12
        }

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
