import QtQuick 2.15
import CustomItems 1.0

import "fTPSingleScripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody
    onWidthChanged: ScoreScripts.updateScoreBoard()
    // Data related
    onClearData: fTPModel.clearData();
    // Point related
    property int pointFontSize: 10
    onPointFontSizeChanged: {
        delegate.pointFontSize = fTPBody.pointFontSize;
        fTPModel.pointFontPointSize = fTPBody.pointFontSize;
    }

    property bool displayPoints: false
    onDisplayPointsChanged:  delegate.pointDisplayVisible = displayPoints
    property int pointDisplayWidth: 20
    property int pointDisplayHeight: 20

    // Score related
    property int scoreFontSize: 48
    onScoreFontSizeChanged: {
        fTPModel.scoreFontPointSize = fTPBody.scoreFontSize;
        delegate.scoreFontSize = fTPBody.scoreFontSize;
    }

    onSizeScale: fTPModel.scale = s

    property int throwsPerRound: 3
    onThrowsPerRoundChanged: fTPModel.throwCount = throwsPerRound;

    onMinimumColumnCountChanged: fTPModel.setMinimumColumnCount(fTPBody.minimumColumnCount)
    onMinimumRowCount: fTPModel.setMinimumRowCount(count);

    // Header related
    horizontalHeaderFontSize: 24
    verticalHeaderVisible: false

    onAppendHeaderData: {
        for(var i = 0; i < data.length;i++)
        {
            var assignedPlayerName = data[i];
            appendHeader(assignedPlayerName,Qt.Horizontal);
            setData(assignedPlayerName,0,defaultVal,undefined);
        }
    }

    property int headerFontSize: 24
    onHeaderFontSizeChanged: fTPModel.headerFontSize = fTPBody.headerFontSize
    headerOrientation: Qt.Horizontal
    verticalHeaderFillMode: 0x1
    horizontalHeaderFillMode: 0x2
    onHeaderOrientationChanged: fTPModel.setHeaderOrientation(headerOrientation)
    onVerticalHeaderFillModeChanged: fTPModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: fTPModel.horizontalFillMode = horizontalHeaderFillMode

    // Cell related
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth

    onPointDisplayWidthChanged: delegate.pointDisplayWidth = pointDisplayWidth

    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    onAppendHeader: ScoreScripts.appendHeader(header,orientation)
    // Manipulate state such as: add score, takescore, edit score
    onSetData: ScoreScripts.setData(playerName,point,score)
    onTakeData: ScoreScripts.takeData(row,column,playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)

    QtObject{
        id: cellPositionHolder

        property int px: -1
        property int py: -1

        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return fTPBody.width / fTPModel.columnCount;
    }

    rowHeightProvider: function(row)
    {
        return fTPBody.height;
        //return myModel.rowHeightAt(row);
    }

    model: FTPSingleDataModel {
        id: fTPModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        throwCount : fTPBody.throwsPerRound
        headerOrientation: fTPBody.headerOrientation
        pointFontPointSize: fTPBody.pointFontSize
        scoreFontPointSize: fTPBody.scoreFontSize
        horizontalFillMode: fTPBody.horizontalHeaderFillMode
        verticalFillMode: fTPBody.verticalHeaderFillMode
        appendMode: DataModelContext.singleThrowInput
    }

    cellDelegate: CellDelegate {
        id: delegate
        cellBorderWidth: fTPBody.cellBorderWidth
        cellColor: "transparent"
        scoreFontSize: fTPBody.scoreFontSize
        pointFontSize: fTPBody.pointFontSize
        pointDisplayVisible: fTPBody.displayPoints
        pointDisplayWidth: fTPBody.pointDisplayWidth
        onTextChanged: notifyCellPosition(delegate.x,delegate.y);
        text: display
    }
}
