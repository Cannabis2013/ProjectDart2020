#ifndef DCMETACONVERTER_H
#define DCMETACONVERTER_H

#include <DartsController/Meta/idcmetaconverter.h>

class QUuid;
class QString;
struct DCMeta;
class QByteArray;
class QJsonObject;
class DCMetaConverter : public IDCMetaConverter<DCMeta>
{
    // IDCMetaConverter interface
public:
    virtual Meta convert(const ByteArray &byteArray) const override;
private:
    QJsonObject toJsonObject(const QByteArray &byteArray) const;
    DCMeta toMeta(const QJsonObject &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // DCMETACONVERTER_H
