#include "dartsaddinputtodb.h"
#include "SLAs/dartsmodelsservices.h"

bool DartsAddInputToDb::add(const ByteArray &byteArray, const QUuid &tournamentID, DartsModelsServices *services)
{
    auto dbContext = services->inputServices()->dbContext();
    auto input = createInput(byteArray,services);
    removeHiddenInputs(tournamentID,services);
    services->inputServices()->dbContext()->add(input);
    return dbContext->saveChanges();
}

DartsAddInputToDb::Model *DartsAddInputToDb::createInput(const ByteArray &byteArray, DartsModelsServices *services) const
{
    auto cvtr = services->inputServices()->inputConverter();
    auto model = cvtr->create(byteArray);
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(DisplayHint);
    return input;
}

void DartsAddInputToDb::removeHiddenInputs(const QUuid &tournamentID, DartsModelsServices *services) const
{
    auto dbContext = services->inputServices()->dbContext();
    dbContext->remove([=](Model *model,const int&){
        auto input = dynamic_cast<IDartsInput*>(model);
        return input->tournamentId() == tournamentID && input->hint() == HiddenHint;
    });
}
