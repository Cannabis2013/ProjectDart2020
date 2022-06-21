#ifndef IDCMETABUILDER_H
#define IDCMETABUILDER_H

struct DCInput;
struct DCPlayer;
class QByteArray;
struct DCIndex;
template<typename T, typename U>
class IDCPlayerManager;
template<typename T, typename U>
class IDCIndexController;
template<typename T>
class IDCMetaManager;

template<typename TMeta>
class IDCMetaBuilder
{
public:
    typedef TMeta Meta;
    typedef IDCMetaManager<Meta> MetaContext;
    typedef IDCIndexController<DCIndex,Meta> IdxCtrl;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlaCtx;
    virtual Meta create(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
    virtual Meta winnerMeta(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
