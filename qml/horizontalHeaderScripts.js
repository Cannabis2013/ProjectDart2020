function count()
{
    return horizontalHeaderRepeater.count;
}
function setData(i, value)
{
    horizontalHeaderRepeater.itemAt(i).children[4].text = value;
}
function setColumnWidth(i, width)
{
    horizontalHeaderRepeater.itemAt(i).width = width;
}

function setBorderWidth(w)
{
    cellBody.bottomBorderWidth = w;
    cellBody.rightBorderWidth = w;
}
