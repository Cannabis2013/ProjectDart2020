#include "dartsinputtojson.h"
#include "SLAs/dartsmodelsservices.h"
#include <qjsondocument.h>
#include "IndexesDbSLAs/idartsindex.h"

DartsInputToJson::ByteArray DartsInputToJson::toJson(const QUuid &tournamentID, const QString &name,
                                                     const ByteArray &indexAsByteArray, const DartsModelsServices *services) const
{
    auto index = services->indexServices()->indexBuilder()->create(indexAsByteArray);
    auto input = getInputModel(index,tournamentID,name,services);
    return toByteArray(input,services);
}

DartsInputToJson::Model *DartsInputToJson::getInputModel(IDartsIndex *index, const QUuid &tournamentID, const QString &name, const DartsModelsServices *services) const
{
    auto dbContext = services->inputServices()->dbContext();
    auto input = dbContext->model([=](Model *model){
        auto input = dynamic_cast<IDartsInput*>(model);
        if(input->tournamentId() != tournamentID)
            return false;
        else if(input->playerName() != name)
            return false;
        else if(input->roundIndex() != index->roundIndex())
            return false;
        else if(input->attempt() != index->attemptIndex())
            return false;
        return true;
    });
    return input;
}

QByteArray DartsInputToJson::toByteArray(Model *model, const DartsModelsServices *services) const
{
    auto cvtr = services->inputServices()->inputConverter();
    auto json = cvtr->create(model);
    return QJsonDocument(json).toJson();
}
