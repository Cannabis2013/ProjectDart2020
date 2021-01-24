import QtQuick 2.0

Rectangle {
    clip: true
    signal setData(string playerName, int point, int score, int keyCode)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int point,int score)
    signal clearData()
    signal minimumRowCount(int count)
    signal appendHeader(string header, int orientation)
    signal sizeScale(double s)
    signal appendHeaderData(var data,int defaultVal)
}
