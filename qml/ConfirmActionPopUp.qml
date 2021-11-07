import QtQuick 2.0

Rectangle{
    id: pageBody
    color: "black"
    anchors.fill: parent
    signal acceptClicked
    onAcceptClicked: destroy()
    signal cancelClicked
    onCancelClicked: pageBody.destroy()
    ConfirmActionBack{
        anchors.fill: parent
    }
    ConfirmActionButtons{
        anchors.fill: parent
    }
}
