#ifndef CREATEDCENTITY_H
#define CREATEDCENTITY_H

#include "icreatedcmetainfo.h"
#include "dcmeta.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class createDCMetaInfo : public ICreateDCMetaInfo
{
public:
    virtual const DCBuilding::IDCMetaInfo* service(const QByteArray &input) const override
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
    const DCBuilding::DCMeta *createMetaInfo(const QJsonObject &jsonObject) const
    {
        auto metaInfo = new DCBuilding::DCMeta;
        initializeMetaInfo(metaInfo,jsonObject);
        return metaInfo;
    }
    void initializeMetaInfo(DCBuilding::DCMeta *metaInfo, const QJsonObject &jsonObject) const
    {
        metaInfo->setTournamentId(QUuid(jsonObject.value("tournamentId").toString()));
        metaInfo->setKeyPoint(jsonObject.value("keyPoint").toInt());
        metaInfo->setInputHint(jsonObject.value("inputHint").toInt());
        metaInfo->setWinnerId(QUuid(jsonObject.value("winnerId").toString()));
        metaInfo->setDisplayHint(jsonObject.value("displayHint").toInt());
    }
};
#endif // BUILDDARTSCONTROLLERENTITY_H
