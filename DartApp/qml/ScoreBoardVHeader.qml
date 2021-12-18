import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreboardscripts.js" as ScoreBoardScripts

Flickable{
    id: scoreBoardVHeaderBody
    clip: true
    interactive: false
    function dataCount()
    {
        return verticalHeader.dataCount();
    }
    function setData(i, value)
    {
        verticalHeader.setData(i, value);
    }
    function setRowHeight(r,h)
    {
        verticalHeader.setRowHeight(r,h);
    }
    property int model: verticalHeader.model
    onModelChanged: verticalHeader.model = model
    VerticalHeader {
        id: verticalHeader
        anchors.fill: parent
        borderWidth: 1
        Layout.alignment: Qt.AlignTop
        visible: scoreBoardBody.verticalHeaderVisible
    }
}
