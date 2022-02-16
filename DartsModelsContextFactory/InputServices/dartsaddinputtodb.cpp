#include "dartsaddinputtodb.h"
#include "SLAs/dartsmodelsservices.h"

DartsAddInputToDb::DartsAddInputToDb(DartsModelsServices *services):_services(services)
{
    _iptServices = _services->inputServices();
    _iptsDb = _iptServices->inputsDb();
}

void DartsAddInputToDb::add(const ByteArray &byteArray, const QUuid &tournamentID)
{
    auto input = createInput(byteArray);
    removeHiddenInputs(tournamentID);
    _iptsDb->add(input);
}

DartsAddInputToDb::Model *DartsAddInputToDb::createInput(const ByteArray &byteArray) const
{
    auto cvtr = _iptServices->inputConverter();
    auto model = cvtr->create(byteArray);
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(DisplayHint);
    return input;
}

void DartsAddInputToDb::removeHiddenInputs(const QUuid &tournamentID) const
{
    auto models = _iptsDb->models();
    QVector<IDartsInput*> tournamentInputs;
    for (const auto &model : qAsConst(models)) {
        auto input = dynamic_cast<IDartsInput*>(model);
        if(input->tournamentId() == tournamentID)
            tournamentInputs << input;
    }
    for (const auto &input : qAsConst(tournamentInputs)) {
        if(input->hint() == HiddenHint)
        {
            auto indexOfModel = _iptsDb->indexOf(input);
            _iptsDb->remove(indexOfModel);
        }
    }
}
