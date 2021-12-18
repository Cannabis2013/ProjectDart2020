#ifndef CreatePlayersContext_H
#define CreatePlayersContext_H
#include <qobject.h>
class AbsPlaCtx;
#ifdef PlaFactLib
    #define PlaFactExport Q_DECL_EXPORT
#else
    #define PlaFactExport Q_DECL_IMPORT
#endif
class PlaFactExport CreatePlayersContext
{
public:
    static AbsPlaCtx *localJson();
};
#endif // LOCALPLAYERSCONTEXT_H
