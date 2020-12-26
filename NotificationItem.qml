import QtQuick 2.0

Item {
    id: notifyBody
    signal setSuggestion(string txt)
    onSetSuggestion: notifyText.text = txt
    Text {
        id: notifyText
        anchors.fill: parent
        text: qsTr("text")
    }
}
