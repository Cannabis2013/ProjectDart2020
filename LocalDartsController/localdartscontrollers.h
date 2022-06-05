#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H

#include <qobject.h>

class AbstractDartsContext;
class AssembleDSC;
class AssembleDPC;
class IDartsCtrl;

class LocalDartsControllers
{
public:
        LocalDartsControllers();
        IDartsCtrl *singlePoint(AbstractDartsContext *modelsContext);
        IDartsCtrl *multiPoint(AbstractDartsContext *modelsContext);
private:
        AssembleDPC *assembleDPC;
        AssembleDSC *assembleDSC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
