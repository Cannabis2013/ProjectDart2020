#ifndef IDCMETABUILDER_H
#define IDCMETABUILDER_H
#include "ModelBuilderSLAs/idcmodelbuilder.h"
class QByteArray;
template<typename T, typename U>
class IDCMetaConverter;
struct TnmVals;
struct DCMeta;
class AbsDCPlayersCtx;
class IDCIndexController;
class IDCMetaContext;
template<typename TModel, typename TJson>
class IDCMetaBuilder : public IDCModelBuilder<TModel,TJson>
{
public:
    typedef TModel Meta;
    typedef QByteArray ByteArray;
    typedef TJson Json;
    typedef IDCMetaContext MetaCtx;
    typedef IDCIndexController IdxCtrl;
    typedef AbsDCPlayersCtx PlaCtx;
    typedef IDCMetaConverter<Meta,ByteArray> MetaCvtr ;
    virtual Meta create(const QByteArray &json) const override = 0;
    virtual Meta create(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
    virtual Meta winnerMeta(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const = 0;
};
#endif // IDCBUILDMETAMODEL_H
