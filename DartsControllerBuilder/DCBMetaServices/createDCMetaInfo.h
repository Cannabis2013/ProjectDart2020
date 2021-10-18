#ifndef CREATEDCENTITY_H
#define CREATEDCENTITY_H

#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "dcmeta.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class createDCMetaInfo : public ICreateDCMetaInfo
{
public:
    virtual DCBuilding::DCMeta service(const QByteArray &input) const override
    {
        auto jsonObject = createJsonObject(input);
        return createMetaInfo(jsonObject);
    }
private:
    QJsonObject createJsonObject(const QByteArray &byteArray) const
    {
        auto document = QJsonDocument::fromJson(byteArray);
        return document.object();
    }
    DCBuilding::DCMeta createMetaInfo(const QJsonObject &jsonObject) const
    {
        DCBuilding::DCMeta metaInfo;
        initializeMetaInfo(metaInfo,jsonObject);
        return metaInfo;
    }
    void initializeMetaInfo(DCBuilding::DCMeta &metaInfo, const QJsonObject &jsonObject) const
    {
        metaInfo.tournamentId = QUuid(jsonObject.value("tournamentId").toString());
        metaInfo.keyPoint = jsonObject.value("keyPoint").toInt();
        metaInfo.inputHint = jsonObject.value("inputHint").toInt();
        metaInfo.winnerId = QUuid(jsonObject.value("winnerId").toString());
        metaInfo.displayHint = jsonObject.value("displayHint").toInt();
    }
};
#endif // BUILDDARTSCONTROLLERENTITY_H
