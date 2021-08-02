import QtQuick 2.12
import QtQuick.Layouts 1.3

Flickable{
    id: flickableHHeader
    clip: true
    contentHeight: 45
    interactive: false
    signal setData(int index, var value)
    onSetData: horizontalHeader.setData(index,value)
    signal setColumnWidth(int index, int w)
    onSetColumnWidth: horizontalHeader.setColumnWidth(index,w)
    readonly property int dataCount: horizontalHeader.dataCount

    property int model: horizontalHeader.model
    onModelChanged: horizontalHeader.model = model
    HorizontalHeader {
        id: horizontalHeader
        anchors.fill: flickableHHeader.contentItem
        backgroundColor: "transparent"
        fontColor: "white"
        borderWidth: 1
        fontSize: 16
    }
}
