import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import "pageScripts.js" as PageScripts
PageInterface {
    id: pageBody
    color: ThemeContext.pageColor
    onDisableBackButton: backButtonDisabled = disable
    onBackButtonVisibleChanged: pageTopBar.showBackButton = backButtonVisible
    onBackButtonDisabledChanged: pageTopBar.enableBackButton = !backButtonDisabled
    onPageContentChanged: PageScripts.setupContent(pageContent)
    onChangePageTitle: pageTopBar.pageTitle = proposedTitle
    onWidthChanged: contentFlickable.contentWidth = contentFlickable.width
    onHeightChanged: contentFlickable.contentHeight = contentFlickable.height
    function handleSetPageIcon(url)
    {
        pageIconUrl = url;
    }
    function handleSetVisible(v)
    {
        visible = v;
    }
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
        anchors.margins: 20
        flow: GridLayout.TopToBottom

        PageTopBar {
            id: pageTopBar
            Layout.fillHeight: true
            Layout.fillWidth: true
            onShowBackButtonChanged: pageBody.backButtonVisible
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
