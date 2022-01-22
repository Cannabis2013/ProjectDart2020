#ifndef DCMETACONVERTER_H
#define DCMETACONVERTER_H
#include <DCMetaSLAs/IDCMetaConverter.h>
class QUuid;
class QString;
struct DCMeta;
class QByteArray;
class QJsonObject;
class DCMetaConverter : public IDCMetaConverter<DCMeta, QByteArray>
{
    // IDCMetaConverter interface
public:
    virtual Meta convert(const Json &byteArray, Meta &meta) const override;
private:
    QJsonObject toJsonObject(const QByteArray &byteArray) const;
    void initByJson(Meta &meta, const QJsonObject &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // DCMETACONVERTER_H
