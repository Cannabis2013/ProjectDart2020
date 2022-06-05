import QtQuick 2.0
Rectangle{
    id: pageBody
    color: "black"
    anchors.fill: parent
    signal acceptClicked
    signal cancelClicked
    onAcceptClicked: pageBody.destroy()
    onCancelClicked: pageBody.destroy()
    ConfirmActionBack{
        anchors.fill: parent
    }
    ConfirmActionButtons{
        anchors.fill: parent
    }
}
