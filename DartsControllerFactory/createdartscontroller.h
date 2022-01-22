#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include <qobject.h>
#ifdef DCFactLib
    #define DCFactExport Q_DECL_EXPORT
#else
    #define DCFactExport Q_DECL_IMPORT
#endif
class CreateDSC;
class CreateDPC;
class AbsDartsCtrl;
class DCFactExport CreateDartsController
{
public:
    CreateDartsController();
    AbsDartsCtrl *pointCtrl();
    AbsDartsCtrl *scoreCtrl();
private:
    CreateDPC *assembleDPC;
    CreateDSC *assembleDSC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
