#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/IDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public IDCJsonBuilder
{
public:
    QByteArray json(const DCMetaInfo &metaInfo) const override;
    QByteArray json(const QVector<DCInput> &inputs) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const override;
    QByteArray json(const DCInput &input, const DCIndexes &indexes, const int &average, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCIndexes &indexes, const DCMetaInfo &metaInfo) const override;
private:
    void setMetaJsonValues(QJsonObject &obj, const DCMetaInfo &metaInfo) const;
    void setTurnValuesJsonValues(QJsonObject &obj, const DCTurnValues &turnValues) const;
    void setInputJsonValues(QJsonObject &obj, const DCInput &input) const;
    void setIndexesJsonValues(QJsonObject &obj, const DCIndexes &indexes) const;
};

#endif // DCJSONBUILDER_H
