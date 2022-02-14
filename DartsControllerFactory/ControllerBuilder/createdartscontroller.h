#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include <qobject.h>
#ifdef DCFactLib
    #define DCFactExport Q_DECL_EXPORT
#else
    #define DCFactExport Q_DECL_IMPORT
#endif
class AbsDartsCtx;
class AssembleDSC;
class AssembleDPC;
class IDartsCtrl;
class DCFactExport CreateDartsController
{
public:
    CreateDartsController();
    IDartsCtrl *pointCtrl(AbsDartsCtx *modelsContext);
    IDartsCtrl *scoreCtrl(AbsDartsCtx *modelsContext);
private:
    AssembleDPC *assembleDPC;
    AssembleDSC *assembleDSC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
