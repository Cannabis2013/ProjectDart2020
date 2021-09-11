function onClicked(text) {
    body.clicked();
    body.clickedAndSendText(text);
}

function onPressed(sustained)
{
    if(sustained)
        body.state = "pressed";
    else
        body.state = checked ? "checked" : "";
}

function onHover(sustained)
{
    if(!body.hoverEnabled)
        return;
    else if(checked)
        return;
    if(sustained)
    {
        body.state = "hovered";
        body.hoveredChanged(true);
    }
    else
    {
        body.state = "";
        body.hoveredChanged(false);
    }
}

function handleClick()
{
    if(isCheckable)
    {
        if(!checked){
            body.state = "checked";
        }
        else
        {
            state = "";
        }
        buttonRect.scale = checked ? checkedScale : 1
        body.checkStateChanged(checked);
    }
}
