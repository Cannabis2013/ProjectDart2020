import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle{
    id: listComponentBody

    color: "transparent"

    signal itemSelected(int index)

    property bool allowCheckState: false
    onAllowCheckStateChanged: listView.allowCheckState = allowCheckState

    property bool allowMultipleSelections: false
    onAllowMultipleSelectionsChanged: listView.allowMultipleSelections = allowMultipleSelections

    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle

    property color itemTextColor: "black"
    onItemTextColorChanged: listView.itemTextColor = itemTextColor

    property int itemFontSize: 10
    onItemFontSizeChanged: listView.itemFontSize = itemFontSize

    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listView.itemSelectedBackgroundColor = itemSelectedBackgroundColor

    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listView.itemSelectedtextColor = itemSelectedtextColor

    property int itemHeight: 50
    onItemHeightChanged: listView.itemHeight = itemHeight

    property int itemWidth : listComponentBody.width
    onItemWidthChanged: listView.itemWidth = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listView.itemHoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listView.hoveredItemTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listView.itemBackgroundColor = itemBackgroundColor

    readonly property int currentlySelectedIndex: listView.getCurrentlySelectedIndex
    readonly property var currentlySelectedIndexes: listView.getCurrentlySelectedIndexes

    function clear()
    {
        listView.clear();
    }

    function addPlayerItem(firstName, lastName, eMail, id){
        listView.addPlayerItem(firstName,lastName,eMail,id);
    }

    function addTournamentItem(tournamentTitle,
                               tournamentMaxPlayers,
                               tournamentLegsCount,
                               tournamentKeyPoint,
                               tournamentPlayersCount)
    {
        listView.addTournamentItem(tournamentTitle,
                                   tournamentMaxPlayers,
                                   tournamentLegsCount,
                                   tournamentKeyPoint,
                                   tournamentPlayersCount);
    }

    clip: true
    GridLayout
    {
        id: bodyLayout

        anchors.fill: parent

        rows:2
        columns: 2

        Label{
            id: labelTitle
            Layout.row: 0
            Layout.column: 0
            text: componentTitle
            font.pointSize: 24

            Layout.fillWidth: true

            horizontalAlignment: Qt.AlignHCenter
        }

        MyListView {
            id: listView
            onItemSelected: listComponentBody.itemSelected(index)
            allowCheckState: listComponentBody.allowCheckState
            itemFontSize: listComponentBody.itemFontSize
            itemTextColor: listComponentBody.itemTextColor
            itemSelectedtextColor: listComponentBody.itemSelectedtextColor
            itemSelectedBackgroundColor: listComponentBody.itemSelectedBackgroundColor
            itemHeight: listComponentBody.itemHeight
            itemWidth: listComponentBody.itemWidth
            Layout.row: 1
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            PropertyAnimation on width {
                from: listComponentBody.width / 2
                to: listComponentBody.width

                duration: 300

                easing.type: Easing.OutBounce
            }
        }
    }
}
