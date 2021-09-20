import QtQuick 2.0

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

Rectangle {
    id: pageBody
    color: ThemeContext.pageColor
    border.width: 0
    signal backButtonPressed
    onBackButtonPressed: pageBody.destroy()
    // Notify Page component that content wants to disable backbutton
    signal requestDisableBackButton(bool disable)
    onRequestDisableBackButton: backButtonDisabled = disable
    property bool backButtonVisible: true
    onBackButtonVisibleChanged: backButton.visible = backButtonVisible
    property bool backButtonDisabled: false
    onBackButtonDisabledChanged: backButton.enabled = !backButtonDisabled
    property Content pageContent: Content{}
    onPageContentChanged: {
        contentFlickable.children[0].children[0] = pageContent;
        pageContent.requestSetPageTitle.connect(handleSetPageTitleRequest);
        pageContent.requestSetPageIcon.connect(handleSetPageIcon);
        pageContent.notifyWidthChange.connect(contentFlickable.setContentWidth);
        pageContent.notifyHeightChange.connect(contentFlickable.setContentHeight);
        pageContent.requestSetVisible.connect(handleSetVisible);
        pageContent.requestQuit.connect(backButtonPressed);
        pageContent.requestDisableBackButton.connect(requestDisableBackButton)
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
    function handleSetVisible(v)
    {
        visible = v;
    }

    property string pageTitle: "Page title"
    onPageTitleChanged: pageTitleComponent.text = pageTitle

    property url pageIconUrl: "qrc:/pictures/Ressources/dartpic.png"
    onPageIconUrlChanged: pageIconUrl.source = pageIconUrl

    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color:ThemeContext.pageColor
    }

    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        rowSpacing: 10
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20

        flow: GridLayout.TopToBottom
        // Top bar
        GridLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            flow: GridLayout.LeftToRight
            PushButton
            {
                id: backButton
                visible: pageBody.backButtonVisible
                Layout.preferredWidth: 65
                Layout.maximumHeight: 30
                Layout.minimumHeight: 30
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                textColor: "white"
                backgroundColor: ThemeContext.pageBackButtonColor
                text: "Back"
                fontSize: 10
                onClicked: backButtonPressed()
                buttonRadius: ThemeContext.pageBackButtonRadius
            }
            Rectangle
            {
                Layout.maximumHeight: 30
                Layout.minimumHeight: 30
                width: 5
                color: "transparent"
            }

            PageIconItem {
                Layout.maximumHeight: 30
                Layout.maximumWidth: 30
                Layout.minimumHeight: 30
                Layout.minimumWidth: 30
            }

            MyLabel{
                id: pageTitleComponent
                Layout.fillWidth: true
                Layout.maximumHeight: 30
                Layout.minimumHeight: 30
                fontSize: 20
                textLeftMargin: 5
                text: pageBody.pageTitle
                fontColor: "white"
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
