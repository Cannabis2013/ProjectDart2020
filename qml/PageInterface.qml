import QtQuick 2.0
Rectangle {
    signal backButtonPressed
    signal disableBackButton(bool disable)
    property bool backButtonVisible: true
    property bool backButtonDisabled: false
    property Content pageContent: Content{}
    signal changePageTitle(string proposedTitle)
}
