import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    signal backButtonPressed

    signal replyFromBackendRecieved(int status,var args)
    signal requestUpdate

    Layout.fillHeight: true
    Layout.fillWidth: true
    Layout.maximumWidth: defaultPageContentWidth
    Layout.alignment: Qt.AlignHCenter

    color: "transparent"

    Component.onCompleted: {
        applicationInterface.stateChanged.connect(requestUpdate);
        applicationInterface.sendStatus.connect(replyFromBackendRecieved);
    }

    Component.onDestruction: {
        applicationInterface.stateChanged.disconnect(requestUpdate);
        applicationInterface.sendStatus.disconnect(replyFromBackendRecieved);
    }

}
