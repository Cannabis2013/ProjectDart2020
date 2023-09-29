#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H

class AbstractDartsContext;
class IDartsController;

class LocalDartsControllers
{
public:
    IDartsController *singlePoint(AbstractDartsContext *modelsContext);
    IDartsController *multiPoint(AbstractDartsContext *modelsContext);
};
#endif // BUILDDARTSSCORECONTROLLER_H
