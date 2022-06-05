#ifndef DCMETABUILDER_H
#define DCMETABUILDER_H

#include <DartsController/Meta/idcmetabuilder.h>


struct DCMeta;
class QUuid;
class QString;
class QJsonObject;

class DCMetaBuilder : public IDCMetaBuilder<DCMeta>
{
public:
    DCMeta create(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const override;
    DCMeta winnerMeta(MetaContext *metaCtx, IdxCtrl *idxCtrl, PlaCtx *plaCtx) const override;
private:
    QJsonObject toJson(const QByteArray &byteArray) const;
    DCMeta toMeta(const QJsonObject &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // DCMETAMODELBUILDER_H
