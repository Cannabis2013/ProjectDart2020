import QtQuick 2.12
import QtQuick.Layouts 1.3


Page{
    id: pageBody

    pageTitle : "Create player"

    pageContent: CreatePlayerBody {
        id: createPlayerBody
    }
    Component.onCompleted: {
        createPlayerBody.sendPlayerDetails.connect(applicationInterface.handleCreatePlayer);
    }
    Component.onDestruction: {
        createPlayerBody.sendPlayerDetails.disconnect(applicationInterface.handleCreatePlayer);
    }
}
