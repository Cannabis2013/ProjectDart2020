import QtQuick 2.15
import CustomItems 1.0

import "scoreBoardScripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody

    // Data related
    onClearData: myModel.clearData();
    // Point related
    property int pointFontSize: 10
    onPointFontSizeChanged: {
        delegate.pointFontSize = fTPBody.pointFontSize;
        myModel.pointFontPointSize = fTPBody.pointFontSize;
    }

    horizontalHeaderFontSize: 24

    property bool displayPoints: false
    onDisplayPointsChanged:  delegate.pointDisplayVisible = displayPoints
    property int pointDisplayWidth: 20
    property int pointDisplayHeight: 20

    // Score related
    property int scoreFontSize: 48
    onScoreFontSizeChanged: {
        myModel.scoreFontPointSize = fTPBody.scoreFontSize;
        delegate.scoreFontSize = fTPBody.scoreFontSize;
    }

    onSizeScale: myModel.scale = s

    property int throwsPerRound: 3
    onThrowsPerRoundChanged: myModel.throwCount = throwsPerRound;

    onMinimumColumnCount: myModel.setMinimumColumnCount(count);
    onMinimumRowCount: myModel.setMinimumRowCount(count);
    headerOrientation: Qt.Horizontal
    // Header related
    property int headerFontSize: 24
    onHeaderFontSizeChanged: {
        myModel.headerFontSize = fTPBody.headerFontSize;

    }
    // Header signal handling related
    onHeaderOrientationChanged: myModel.setHeaderOrientation(headerOrientation)
    onVerticalHeaderFillModeChanged: myModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: myModel.horizontalFillMode = horizontalHeaderFillMode

    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth

    onPointDisplayWidthChanged: delegate.pointDisplayWidth = pointDisplayWidth

    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    onAppendHeader: ScoreScripts.appendHeader(header,orientation)

    onSetData: ScoreScripts.setData(playerName,point,score)
    onTakeData: ScoreScripts.takeData(playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)

    QtObject{
        id: cellPositionHolder

        property int px: -1
        property int py: -1

        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return fTPBody.width / myModel.columnCount;
    }

    rowHeightProvider: function(row)
    {
        return fTPBody.height;
        //return myModel.rowHeightAt(row);
    }

    model: FTPDataModel {
        id: myModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        throwCount : fTPBody.throwsPerRound
        headerOrientation: fTPBody.headerOrientation
        pointFontPointSize: fTPBody.pointFontSize
        scoreFontPointSize: fTPBody.scoreFontSize
        appendMode: 0x4
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
