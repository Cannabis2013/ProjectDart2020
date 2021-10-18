#ifndef DCINDEXESBUILDER_H
#define DCINDEXESBUILDER_H

#include "dcindexes.h"
#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCIndexSLAs/idcindexesbuilder.h"

class DCIndexesBuilder : public IDCIndexesBuilder
{
public:
    DCIndexes buildIndexes(const QByteArray &json) const override
    {
        DCIndexes indexes;
        auto jsonObject = toJsonObject(json);
        indexes.totalTurns = jsonObject.value("totalTurns").toInt();
        indexes.turnIndex = jsonObject.value("turnIndex").toInt();
        indexes.roundIndex = jsonObject.value("roundIndex").toInt();
        indexes.setIndex = jsonObject.value("setIndex").toInt();
        indexes.attemptIndex = jsonObject.value("attemptIndex").toInt();
        return indexes;
    }
    DCIndexes buildIndexes(const IDCIndexService *indexService) const override
    {
        DCIndexes indexes;
        indexes.totalTurns = indexService->totalIndex();
        indexes.turnIndex = indexService->turnIndex();
        indexes.roundIndex = indexService->roundIndex();
        indexes.setIndex = indexService->setIndex();
        indexes.attemptIndex = indexService->attemptIndex();
        return indexes;
    }
private:
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        return document.object();
    }
};

#endif // DARTSCONTROLLERINDEXESBUILDER_H
