function updateViewPosition(x,y)
{
    flickableTable.contentX = x;
    flickableTable.contentY = y;
}

function updateContentDimensions(h,w)
{
    flickableVHeader.contentHeight = h;
    flickableTable.contentHeight = h;
    flickableTable.contentWidth = w;
    flickableHHeader.contentWidth = w;
}

function updateVerticalHeaderWidth(w)
{
    flickableVHeader.Layout.minimumWidth = w;
    verticalHeader.width = w;
}
