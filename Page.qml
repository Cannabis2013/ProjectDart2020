import QtQuick 2.0

import QtQuick.Layouts 1.3

Rectangle {

    id: pageBody

    color: defaultBackgroundColor

    property string defaultBackgroundColor: "#A54141"

    signal backButtonPressed
    onBackButtonPressed: pageBody.destroy()

    property Content pageContent: Content{}
    onPageContentChanged: {
        pageLayout.children[2] = pageContent;
        pageContent.backButtonPressed.connect(backButtonPressed);
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
        anchors.bottomMargin: 20

        flow: GridLayout.TopToBottom

        GridLayout{

            Layout.fillWidth: true
            Layout.fillHeight: true

            flow: GridLayout.LeftToRight

            PushButton
            {
                width: 65
                height: 30

                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                textColor: "white"
                backgroundColor: "green"
                text: "Back"
                fontSize: 10
                onClicked: backButtonPressed()
            }

            MyLabel{

                id: pageTitleComponent
                Layout.fillWidth: true
                Layout.minimumHeight: 30
                Layout.maximumHeight: 30
                fontSize: 20
                textLeftMargin: 10

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
    PropertyAnimation on width {
        from: 0
        to: width

        duration: 100
    }
}
