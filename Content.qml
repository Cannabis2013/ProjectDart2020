import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    signal backButtonPressed
    signal sendStatusRequest()
    signal replyFromBackendRecieved(int status,var args)
    signal requestUpdate

    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.maximumWidth: defaultPageContentWidth
    Layout.alignment: Qt.AlignHCenter

    color: "transparent"

    Component.onCompleted: {
        localDart.stateChanged.connect(requestUpdate);
        localDart.sendStatus.connect(replyFromBackendRecieved);
        sendStatusRequest.connect(localDart.handleStatusRequest);
    }

    Component.onDestruction: {
        sendStatusRequest.disconnect(localDart.handleStatusRequest);
        localDart.stateChanged.disconnect(requestUpdate);
        localDart.sendStatus.disconnect(replyFromBackendRecieved);
    }

}
