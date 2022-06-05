function updateViewPosition(x,y)
{
    scoreBoardTableView.contentX = x;
    scoreBoardTableView.contentY = y;
}

function updateContentDimensions(h,w)
{
    scoreBoardVHeader.contentHeight = h;
    scoreBoardTableView.contentHeight = h;
    scoreBoardTableView.contentWidth = w;
    scoreBoardHHeader.contentWidth = w;
}

function updateVerticalHeaderWidth(w)
{
    scoreBoardVHeader.Layout.minimumWidth = w;
    scoreBoardVHeader.width = w;
}
