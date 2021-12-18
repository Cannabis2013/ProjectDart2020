import QtQuick 2.0

Rectangle {
    clip: true
    signal clearData()
    signal minimumRowCount(int count)
    signal appendHeader(var data)
    signal appendHeaderData(var data,int defaultVal)
    signal sizeScale(double s)
    property bool verticalHeaderVisible: true
    property bool horizontalHeaderVisible: true
    signal setHorizontalHeaderModel(int m)
    signal setVerticalHeaderModel(int m)
    signal setHorizontalHeaderDataAt(int j, var val)
    signal setVerticalHeaderDataAt(int i, var val)
}
