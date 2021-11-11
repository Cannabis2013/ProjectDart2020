#ifndef DCINDEXESBUILDER_H
#define DCINDEXESBUILDER_H

#include "dcindex.h"
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCIndexSLAs/idcindexbuilder.h"

class DCInputIndexBuilder : public IDCIndexBuilder
{
public:
    DCIndex index(const QJsonObject &obj) const override
    {
        DCIndex indexes;
        indexes.totalTurns = obj.value("totalTurns").toInt();
        indexes.turnIndex = obj.value("turnIndex").toInt();
        indexes.roundIndex = obj.value("roundIndex").toInt();
        indexes.setIndex = obj.value("setIndex").toInt();
        indexes.attemptIndex = obj.value("attemptIndex").toInt();
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
