#ifndef DCMETABUILDER_H
#define DCMETABUILDER_H
#include "DCMetaSLAs/idcmetabuilder.h"
class QUuid;
class QString;
class QJsonObject;
class DCMetaBuilder : public IDCMetaBuilder<DCMeta,QByteArray>
{
public:
    DCMeta create(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const override;
    DCMeta create(const QByteArray &json) const override;
    DCMeta winnerMeta(MetaCtx *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const override;
private:
    QJsonObject toJson(const ByteArray &byteArray) const;
    DCMeta toMeta(const QJsonObject &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // DCMETAMODELBUILDER_H
