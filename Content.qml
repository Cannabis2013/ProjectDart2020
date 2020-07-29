import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    signal backButtonPressed

    signal replyFromBackendRecieved(int status,var args)
    signal requestUpdate
    signal notifyWidthChange(double w)
    signal notifyHeightChange(double h)

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
            height = minimumHeight
        notifyHeightChange(height);
    }

    Component.onCompleted: {
        applicationInterface.stateChanged.connect(requestUpdate);
        applicationInterface.sendStatus.connect(replyFromBackendRecieved);
    }

    Component.onDestruction: {
        applicationInterface.stateChanged.disconnect(requestUpdate);
        applicationInterface.sendStatus.disconnect(replyFromBackendRecieved);
    }
}
