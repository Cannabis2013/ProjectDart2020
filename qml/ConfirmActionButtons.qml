import QtQuick 2.0
import QtQuick.Layouts 1.3
GridLayout{
    flow: GridLayout.LeftToRight
    PushButton{
        id: cancelButton
        text: qsTr("Cancel")
        Layout.minimumWidth: 128
        Layout.maximumWidth: 128
        Layout.bottomMargin: 10
        height: 48
        fontSize: 20
        buttonRadius: 10
        backgroundColor: "red"
        hoveredColor: "red"
        textColor: "white"
        Layout.alignment: Qt.AlignBottom | Qt.AlignRight
        onClicked: pageBody.cancelClicked();
    }
    PushButton{
        id: acceptButton
        text: qsTr("Accept")
        Layout.minimumWidth: 128
        Layout.maximumWidth: 128
        Layout.bottomMargin: 10
        height: 48
        fontSize: 20
        backgroundColor: "green"
        hoveredColor: "green"
        textColor: "white"
        buttonRadius: 10
        Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
        onClicked: pageBody.acceptClicked()
    }
}
