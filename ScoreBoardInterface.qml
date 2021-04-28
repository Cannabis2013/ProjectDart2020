import QtQuick 2.0

Rectangle {
    clip: true
    signal clearData()
    signal minimumRowCount(int count)
    signal appendHeader(string header, int orientation)
    signal sizeScale(double s)
    signal appendHeaderData(var data,int defaultVal)

}
