import QtQuick 2.15
import CustomItems 1.0

import "scoreBoardScripts.js" as ScoreScripts

ScoreBoard {
    id: body

    // Data related
    onClearData: myModel.clearData();
    // Point related
    property int pointFontSize: 10
    property bool displayPoints: false
    property int pointDisplayWidth: 20
    property int pointDisplayHeight: 20

    // Score related
    property int scoreFontSize: 20

    onSizeScale: myModel.scale = s

    property int throwsPerRound: 3
    onThrowsPerRoundChanged: myModel.throwCount = throwsPerRound;

    onMinimumColumnCount: myModel.setMinimumColumnCount(count);
    onMinimumRowCount: myModel.setMinimumRowCount(count);
    headerOrientation: Qt.Vertical
    // Header signal handling related
    onHeaderOrientationChanged: myModel.setHeaderOrientation(headerOrientation)
    onVerticalHeaderFillModeChanged: myModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: myModel.horizontalFillMode = horizontalHeaderFillMode
    onPointFontSizeChanged: {
        delegate.pointFontSize = body.pointFontSize;
        myModel.pointFontPointSize = body.pointFontSize;
    }
    onScoreFontSizeChanged: {
        myModel.scoreFontPointSize = body.scoreFontSize;
        delegate.scoreFontSize = body.scoreFontSize;
    }

    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    onDisplayPointsChanged:  delegate.pointDisplayVisible = displayPoints
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

    columnWidthProvider: function(column)
    {
        return myModel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return myModel.rowHeightAt(row);
    }

    model: FTPDataModel {
        id: myModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        throwCount : body.throwsPerRound
        headerOrientation: body.headerOrientation
        pointFontPointSize: body.pointFontSize
        scoreFontPointSize: body.scoreFontSize
        appendMode: 0x8
    }

    cellDelegate: CellDelegate {
        id: delegate
        cellBorderWidth: body.cellBorderWidth
        cellColor: "purple"
        scoreFontSize: body.scoreFontSize
        pointFontSize: body.pointFontSize
        pointDisplayVisible: body.displayPoints
        pointDisplayWidth: body.pointDisplayWidth
        onTextChanged: notifyCellPosition(delegate.x,delegate.y);
        text: display
    }
}
