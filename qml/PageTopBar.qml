import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
GridLayout{
    id: pageTopBar
    flow: GridLayout.LeftToRight
    property bool showBackButton: true
    onShowBackButtonChanged: backButton.visible = showBackButton
    property string pageTitle: "Page"
    onPageTitleChanged: pageTitleComponent.text = pageTitle
    property bool enableBackButton: true
    onEnableBackButtonChanged: backButton.enabled = enableBackButton
    PushButton
    {
        id: backButton
        visible: pageTopBar.showBackButton
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
        enabled : pageTopBar.enableBackButton
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
        text: pageTopBar.pageTitle
        fontColor: "white"
    }
}
