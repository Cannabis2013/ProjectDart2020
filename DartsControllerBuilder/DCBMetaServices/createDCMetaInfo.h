#ifndef CREATEDCENTITY_H
#define CREATEDCENTITY_H

#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "dcbmeta.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class CreateDCMetaInfo : public ICreateDCMetaInfo
{
public:
    virtual DCBMeta service(const QByteArray &input) const override
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
    DCBMeta createMetaInfo(const QJsonObject &jsonObject) const
    {
        DCBMeta metaInfo;
        initializeMetaInfo(metaInfo,jsonObject);
        return metaInfo;
    }
    void initializeMetaInfo(DCBMeta &metaInfo, const QJsonObject &jsonObject) const
    {
        metaInfo.tournamentId = QUuid(jsonObject.value("tournamentId").toString());
        metaInfo.initialRemainingScore = jsonObject.value("keyPoint").toInt();
        metaInfo.inputHint = jsonObject.value("inputHint").toInt();
        metaInfo.winnerId = QUuid(jsonObject.value("winnerId").toString());
    }
};
#endif // BUILDDARTSCONTROLLERENTITY_H
