import QtQuick 2.0
import QtQuick.Layouts 1.3

GridLayout{
    flow: GridLayout.TopToBottom

    QtObject{
        id: defaultTextLabels
        property string throwSuggestLabel: "Target row:"
        property string winnerLabel: "Winner:"
    }

    signal clear()
    onClear: {
        winnerText.text = "";
        suggestText.text = "";
    }

    function setCurrentWinner(text)
    {
        if(text !== "")
        {
            winnerText.visible = true;
            winnerText.text = defaultTextLabels.winnerLabel + text;
        }
        else
            winnerText.visible = false;
    }

    function setThrowSuggestion(text)
    {
        if(text !== "")
        {
            suggestText.visible = true;
            suggestText.text = defaultTextLabels.throwSuggestLabel + text;
        }
        else
            suggestText.visible = false;
    }
    Rectangle{
        color: "transparent"
        Layout.fillHeight: true
    }

    Text {
        id: winnerText
        text: qsTr(defaultTextLabels.winnerLabel)
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 16
        Layout.alignment: Qt.AlignBottom
        color: ThemeContext.keyTextDisplayColor
        visible: false
    }
    Text {
        id: suggestText
        text: qsTr(defaultTextLabels.throwSuggestLabel)
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 16
        Layout.alignment: Qt.AlignBottom
        color: ThemeContext.keyTextDisplayColor
        visible: false
    }
}
