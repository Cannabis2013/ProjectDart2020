#ifndef CREATEDARTSCONTEXT_H
#define CREATEDARTSCONTEXT_H
#include <qobject.h>

class AbsDartsCtx;
class AbsPlaCtx;
#ifdef DartsMdFactLib
    #define DartsFactoryExport Q_DECL_EXPORT
#else
    #define DartsFactoryExport Q_DECL_IMPORT
#endif
class DartsFactoryExport CreateDartsContext
{
public:
    AbsDartsCtx *localJson(AbsPlaCtx *playersContext) const;
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
