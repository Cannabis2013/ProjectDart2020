#ifndef DSCREQINDEXBUILDER_H
#define DSCREQINDEXBUILDER_H
#include <DartsController/DCIndexSLAs/idcreqinputindexbuilder.h>
class DSCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual DCIndex indexes(const IDCIndexController *controller) const override
    {
        DCIndex indexes;
        indexes.totalTurns = controller->totalIndex();
        indexes.turnIndex = controller->turnIndex();
        indexes.roundIndex = controller->roundIndex() - 1;
        indexes.setIndex = controller->setIndex();
        indexes.attemptIndex = controller->attemptIndex();
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
#endif // DSCREQINDEXBUILDER_H
