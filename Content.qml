import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    // Basic properties (color, clip, size)
    color: "transparent"
    clip: true
    anchors.fill: parent
    // Signals
    signal requestQuit
    signal replyFromBackendRecieved(int response,var args)
    signal requestUpdate
    signal requestSetVisible(bool v)
    signal notifyWidthChange(double w)
    signal notifyHeightChange(double h)
    signal requestSetPageTitle(string title)
    signal requestSetPageIcon(url url)
    signal requestDisableBackButton(bool disable)

    property bool isPopUp: false
    onIsPopUpChanged: applicationInterface.transmitResponse.disconnect(replyFromBackendRecieved);

    property double minimumHeight: 0
    property double minimumWidth: 0

    onWidthChanged: {
        if(width < minimumWidth)
            width = minimumWidth;
        notifyWidthChange(width);
    }

    onHeightChanged: {
        if(height < minimumHeight)
            height = minimumHeight;
        notifyHeightChange(height);
    }

    Component.onCompleted: {
        applicationInterface.transmitResponse.connect(replyFromBackendRecieved);
    }

    Component.onDestruction: {
        applicationInterface.transmitResponse.disconnect(replyFromBackendRecieved);
    }
}
