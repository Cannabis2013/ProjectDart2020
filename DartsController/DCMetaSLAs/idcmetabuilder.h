#ifndef IDCMETABUILDER_H
#define IDCMETABUILDER_H
struct DCInput;
struct DCPlayer;
class QByteArray;
struct TnmVals;
struct DCIndex;
struct DCMeta;
template<typename T, typename U>
class AbsDCPlayersCtx;
template<typename T, typename U>
class IDCIndexController;
template<typename T>
class IDCMetaService;
template<typename TModel>
class IDCMetaBuilder
{
public:
    typedef TModel Meta;
    typedef IDCMetaService<DCMeta> MetaContext;
    typedef IDCIndexController<DCIndex,DCMeta> IdxCtrl;
    typedef AbsDCPlayersCtx<DCPlayer,DCInput> PlaCtx;
    virtual Meta create(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
    virtual Meta winnerMeta(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
