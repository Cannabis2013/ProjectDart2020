#ifndef CREATEDCENTITY_H
#define CREATEDCENTITY_H

#include "icreatedcmetainfo.h"
#include "dcmeta.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class createDCMetaInfo : public ICreateDCMetaInfo
{
public:
    virtual const DartsBuilderContext::IDCMetaInfo* service(const QByteArray &input) const override
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
    const DartsBuilderContext::DCMeta *createMetaInfo(const QJsonObject &jsonObject) const
    {
        auto metaInfo = new DartsBuilderContext::DCMeta;
        initializeMetaInfo(metaInfo,jsonObject);
        return metaInfo;
    }
    void initializeMetaInfo(DartsBuilderContext::DCMeta *metaInfo, const QJsonObject &jsonObject) const
    {
        metaInfo->setTournamentId(QUuid(jsonObject.value("tournamentId").toString()));
        metaInfo->setAttempt(jsonObject.value("attempts").toInt());
        metaInfo->setKeyPoint(jsonObject.value("keyPoint").toInt());
        metaInfo->setTerminalKeyCode(jsonObject.value("terminalKeyCode").toInt());
        metaInfo->setInputHint(jsonObject.value("inputHint").toInt());
        metaInfo->setWinnerId(QUuid(jsonObject.value("winnerId").toString()));
        metaInfo->setDisplayHint(jsonObject.value("displayHint").toInt());
    }
};
#endif // BUILDDARTSCONTROLLERENTITY_H
