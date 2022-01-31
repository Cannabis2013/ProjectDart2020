#include "dartsinputtojson.h"
#include "SLAs/dmcservices.h"

#include <qjsondocument.h>

DartsInputToJson::DartsInputToJson(DMCServices *services):_services(services)
{
    _iptServices = services->inputServices();
    _iptsDb = services->inputServices()->inputsDb();
    _idxBuilder = _services->indexServices()->indexBuilder();
    _cvtr = _services->inputServices()->inputConverter();
}

DartsInputToJson::ByteArray DartsInputToJson::toJson(const QUuid &tournamentID, const QString &name, const ByteArray &idxBa) const
{
    auto index = _idxBuilder->create(idxBa);
    auto input = _iptsDb->model([=](Model *model){
        auto input = dynamic_cast<IDartsInput*>(model);
        if(input->tournamentId() != tournamentID)
            return false;
        else if(input->roundIndex() != index->roundIndex())
            return false;
        else if(input->playerName() != name)
            return false;
        else if(input->attempt() != index->attemptIndex())
            return false;
        else
            return true;
    });
    auto json = _cvtr->create(input);
    return QJsonDocument(json).toJson();
}
