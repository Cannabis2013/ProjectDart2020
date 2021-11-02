function setupContent(pageContent)
{
    contentFlickable.children[0].children[0] = pageContent;
    pageTopBar.pageTitle = pageContent.preferedPageTitle;
    pageContent.requestSetPageIcon.connect(handleSetPageIcon);
    pageContent.notifyWidthChange.connect(contentFlickable.setContentWidth);
    pageContent.notifyHeightChange.connect(contentFlickable.setContentHeight);
    pageContent.requestChangePageTitle.connect(pageBody.changePageTitle);
    pageContent.requestSetVisible.connect(handleSetVisible);
    pageContent.requestQuit.connect(backButtonPressed);
    pageContent.requestDisableBackButton.connect(requestDisableBackButton)
    pageContent.anchors.fill = contentFlickable.contentItem;
}
