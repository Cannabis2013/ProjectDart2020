import QtQuick 2.0
import QtQuick.Layouts 1.3

Item{
    id: displayBody
    height: 40
    QtObject{
        id: defaultTextLabels
        property string throwSuggestLabel: "Finish with: "
        property string winnerLabel: "Winner: "
    }
    signal clear()
    onClear: {
        winnerText.text = "";
        suggestText.text = "";
    }
    function setCurrentWinner(text)
    {
        if(text !== "")
            winnerText.text = defaultTextLabels.winnerLabel + text;
        else
            winnerText.text = "";
    }

    function setThrowSuggestion(text)
    {
        if(text !== "")
            suggestText.text = defaultTextLabels.throwSuggestLabel + text;
        else
            suggestText.text = "";
    }
    Rectangle{
        color: "transparent"
        anchors.fill: parent
    }
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.LeftToRight
        Text {
            id: winnerText
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pointSize: 16
            color: ThemeContext.keyTextDisplayColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            visible: true
            Layout.minimumWidth: displayBody.width *0.5
            Layout.maximumWidth: displayBody.width *0.5
        }
        Text {
            id: suggestText
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pointSize: 16
            color: ThemeContext.keyTextDisplayColor
            visible: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.minimumWidth: displayBody.width *0.5
            Layout.maximumWidth: displayBody.width *0.5
        }
    }
}
