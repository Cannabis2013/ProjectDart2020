#ifndef DCINDEXESBUILDER_H
#define DCINDEXESBUILDER_H

#include "dcindex.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCIndexSLAs/idcinputindexbuilder.h"

class DCInputIndexBuilder : public IDCInputIndexBuilder
{
public:
    DCIndex index(const QByteArray &json) const override
    {
        DCIndex indexes;
        auto jsonObject = toJsonObject(json);
        indexes.totalTurns = jsonObject.value("totalTurns").toInt();
        indexes.turnIndex = jsonObject.value("turnIndex").toInt();
        indexes.roundIndex = jsonObject.value("roundIndex").toInt();
        indexes.setIndex = jsonObject.value("setIndex").toInt();
        indexes.attemptIndex = jsonObject.value("attemptIndex").toInt();
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
