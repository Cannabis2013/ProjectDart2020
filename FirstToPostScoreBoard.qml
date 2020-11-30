import QtQuick 2.15
import CustomItems 1.0

import "scoreBoardScripts.js" as ScoreScripts

ScoreBoard {
    id: body

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
    // Header signal handling related
    onHeaderOrientationChanged: myModel.setHeaderOrientation(headerOrientation)
    onVerticalHeaderFillModeChanged: myModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: myModel.horizontalFillMode = horizontalHeaderFillMode
    onPointFontSizeChanged: {
        cellDelegate.pointFontSize = pointFontSize;
        myModel.pointFontPointSize = pointFontSize;
        }

    onScoreFontSizeChanged: {
        myModel.scoreFontPointSize = scoreFontSize;
        cellDelegate.scoreFontSize = scoreFontSize;
    }

    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.borderWidth = cellBorderWidth
    onDisplayPointsChanged:  cellDelegate.pointDisplayVisible = displayPoints
    onPointDisplayWidthChanged: cellDelegate.pointDisplayWidth = pointDisplayWidth

    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    onAppendHeader: {
        myModel.appendHeaderItem(header,headerOrientation);
        var preferedWidth = myModel.preferedHeaderItemWidth(orientation);
        body.updateVerticalHeaderWidth(preferedWidth);
    }

    onSetData: {
        var result = myModel.insertData(playerName,point,score);
        if(!result)
            print("Couldn't add data to model");
    }
    onTakeData:
    {
        var result = myModel.removeLastItem(playerName);
        if(!result)
            print("Couldn't take data");
    }
    onEditData:
    {
        var result = myModel.editData(row,column,point,score);
        if(!result)
            print("Couldn't edit data");
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

        horizontalFillMode: 0x1
        verticalFillMode: 0x2
    }

    cellDelegate: CellDelegate {
        id: cellDelegate
        cellBorderWidth: body.cellBorderWidth
        cellColor: "purple"
        scoreFontSize: body.scoreFontSize
        pointFontSize: body.pointFontSize
        pointDisplayVisible: body.displayPoints
        pointDisplayWidth: body.pointDisplayWidth
        onNotifyLocation: notifyCellPosition(x,y)
        text: display
    }
}
