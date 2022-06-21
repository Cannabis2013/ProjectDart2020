#ifndef DCCREATEWINNERREPORT_H
#define DCCREATEWINNERREPORT_H

#include <DartsController/Contracts/Routines/idccreatewinnerjson.h>

class QJsonObject;
template<typename T> class IDCModelToJson;
struct DCInput;
template<typename T> class IDCMetaManager;
struct DCMeta;
class DCServices;

class DCCreateWinnerReport : public IDCCreateWinnerJson
{
public:
    typedef IDCModelToJson<DCInput> InputToJson;
    typedef IDCMetaManager<DCMeta> MetaManager;
    DCCreateWinnerReport(DCServices *services);
    virtual QByteArray create() const override;
private:
    QJsonObject createWinnerJson(const DCMeta &meta) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    MetaManager *_metaManager;
    InputToJson *_inputToJson;
};

#endif // DCCREATEWINNERREPORT_H
