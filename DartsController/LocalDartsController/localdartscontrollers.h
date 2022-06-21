#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H

class AbstractDartsContext;
class IDartsCtrl;

class LocalDartsControllers
{
public:
        IDartsCtrl *singlePoint(AbstractDartsContext *modelsContext);
        IDartsCtrl *multiPoint(AbstractDartsContext *modelsContext);
};
#endif // BUILDDARTSSCORECONTROLLER_H
