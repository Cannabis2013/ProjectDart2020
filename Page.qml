import QtQuick 2.0

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

Rectangle {
    id: pageBody
    signal backButtonPressed
    color: defaultBackgroundColor
    property string defaultBackgroundColor: "#A54141"
    onBackButtonPressed: pageBody.destroy()
    property bool backButtonDisabled: false
    onBackButtonDisabledChanged: backButton.enabled = !backButtonDisabled
    property Content pageContent: Content{}
    onPageContentChanged: {
        contentFlickable.children[0].children[0] = pageContent;
        pageContent.requestSetPageTitle.connect(pageBody.handleSetPageTitleRequest);
        pageContent.requestSetPageIcon.connect(pageBody.handleSetPageIcon);
        pageContent.notifyWidthChange.connect(contentFlickable.setContentWidth);
        pageContent.notifyHeightChange.connect(contentFlickable.setContentHeight);
        pageContent.backButtonPressed.connect(backButtonPressed);
        pageContent.anchors.fill = contentFlickable.contentItem;
    }
    onWidthChanged: {
        contentFlickable.contentWidth = contentFlickable.width;
    }
    onHeightChanged: {
        contentFlickable.contentHeight = contentFlickable.height;
    }

    function handleSetPageTitleRequest(title)
    {
        pageTitle = title;
    }

    function handleSetPageIcon(url)
    {
        pageIconUrl = url;
    }

    property string pageTitle: "Page title"
    onPageTitleChanged: pageTitleComponent.text = pageTitle

    property url pageIconUrl: "qrc:/pictures/Ressources/dartpic.png"
    onPageIconUrlChanged: pageIcon.source = pageIconUrl

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
                id: backButton
                Layout.preferredWidth: 65
                Layout.maximumHeight: 30
                Layout.minimumHeight: 30
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                textColor: "white"
                backgroundColor: "green"
                text: "Back"
                fontSize: 10
                onClicked: backButtonPressed()
            }
            Image {
                id: pageIcon
                Layout.minimumHeight: 30
                Layout.maximumHeight: 30
                Layout.minimumWidth: 30
                Layout.maximumWidth: 30
                source: "qrc:/pictures/Ressources/dartpic.png"
            }
            MyLabel{
                id: pageTitleComponent
                Layout.fillWidth: true
                Layout.maximumHeight: 30
                Layout.minimumHeight: 30
                fontSize: 20
                textLeftMargin: 5
                text: pageBody.pageTitle
            }
        }

        MyRectangle
        {
            id: upperLayoutSpacer
            topBorderWidth: 1
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
        }

        Flickable{
            id: contentFlickable
            clip: true

            function setContentWidth(w)
            {
                contentWidth = w;
            }

            function setContentHeight(h)
            {
                contentHeight = h;
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: defaultPageContentWidth
            Layout.alignment: Qt.AlignHCenter

            Content{
                id: itemPlaceHolder
            }
        }
    }
    PropertyAnimation on x {
        from: - width
        to: 0
        duration: 150
    }
    Component.onCompleted: {
        contentFlickable.contentHeight = contentFlickable.height;
        contentFlickable.contentWidth = contentFlickable.width;
    }
}
