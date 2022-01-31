#include "dartssetipthint.h"
#include "InputsDbSLAs/igetinputs.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "InputModelsSLAs/idartsinput.h"
#include "SLAs/dmcservices.h"

DartsSetIptHint::DartsSetIptHint(DMCServices *services):_services(services)
{
    _iptServices = services->inputServices();
    _iptsDb = services->inputServices()->inputsDb();
    _idxCvtr = services->indexServices()->indexBuilder();
}

void DartsSetIptHint::setHidden(QUuid tournamentID, QString name, const QByteArray &idxBa) const
{
    auto index = _idxCvtr->create(idxBa);
    auto model = _iptsDb->model([=](Model *model){
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
    if(model != nullptr)
        setHint(model,HiddenHint);
}

void DartsSetIptHint::setVisible(QUuid tournamentID, QString name, const QByteArray &idxBa) const
{
    auto index = _idxCvtr->create(idxBa);
    auto model = _iptsDb->model([=](Model *model){
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
    if(model != nullptr)
        setHint(model,DisplayHint);
}

void DartsSetIptHint::setVisible(Model *input) const
{
    setHint(input,DisplayHint);
}

void DartsSetIptHint::setHint(Model *model, const ModelDisplayHint &hint) const
{
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(hint);
}
