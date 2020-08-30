import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    signal backButtonPressed
    signal replyFromBackendRecieved(int response,var args)
    signal requestUpdate
    signal notifyWidthChange(double w)
    signal notifyHeightChange(double h)
    signal requestSetPageTitle(string title)
    signal requestSetPageIcon(url url)

    property bool isPopUp: false
    onIsPopUpChanged: applicationInterface.transmitResponse.disconnect(replyFromBackendRecieved);
    clip: true

    property double minimumHeight: 0
    property double minimumWidth: 0

    color: "transparent"

    anchors.fill: parent

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
