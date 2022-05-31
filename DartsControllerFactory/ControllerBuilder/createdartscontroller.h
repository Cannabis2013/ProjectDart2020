#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include <qobject.h>
#ifdef DCFactLib
    #define DCFactExport Q_DECL_EXPORT
#else
    #define DCFactExport Q_DECL_IMPORT
#endif
class AbstractDartsContext;
class AssembleDSC;
class AssembleDPC;
class IDartsCtrl;
class DCFactExport CreateDartsController
{
public:
    CreateDartsController();
    IDartsCtrl *pointCtrl(AbstractDartsContext *modelsContext);
    IDartsCtrl *scoreCtrl(AbstractDartsContext *modelsContext);
private:
    AssembleDPC *assembleDPC;
    AssembleDSC *assembleDSC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
