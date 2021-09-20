function onHover(sustained)
{
    if(sustained && body.state !== "checked")
        body.state = "hovered";
    else
        body.state = isCheckable && checked ? "checked" : "";
}
function onPressAndHold()
{
    if(noDelayPressSelect || !isCheckable)
        return;
    if(body.isCheckable && !checked)
    {
        body.state = "checked";
        checkMarkScaleAni.start();
    }
    else
        body.state = "";
}
function onClick()
{
    if(!checked)
        body.clicked();
    if(!noDelayPressSelect)
        return;
    if(body.isCheckable && !checked)
    {
        body.state = "checked";
        checkMarkScaleAni.start();
    }
    else
        body.state = "";
}
