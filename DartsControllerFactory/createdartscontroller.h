#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include <qobject.h>
#ifdef DCFactLib
    #define DCFactExport Q_DECL_EXPORT
#else
    #define DCFactExport Q_DECL_IMPORT
#endif
class AbsDartsCtrl;
class DCFactExport CreateDartsController
{
public:
    AbsDartsCtrl *pointCtrl();
    AbsDartsCtrl *scoreCtrl();
};
#endif // BUILDDARTSSCORECONTROLLER_H
