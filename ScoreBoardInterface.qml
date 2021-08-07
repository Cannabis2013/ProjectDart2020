import QtQuick 2.0

Rectangle {
    clip: true
    signal clearData()
    signal minimumRowCount(int count)
    signal appendHeader(var data)
    signal appendHeaderData(var data,int defaultVal)
    signal sizeScale(double s)
}
