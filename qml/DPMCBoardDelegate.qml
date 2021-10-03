import QtQuick 2.15
import CustomItems 1.0

ScoreBoardDelegate {
    id: delegate
    cellColor: "transparent"
    cellBorderWidth: 0
    cellBorderRadius: 10
    property string point: ""
    onPointChanged: pointTextRect.text = point
    DPMCPointRect {
        id: pointTextRect
        x: 3
        y: 3
    }
}
