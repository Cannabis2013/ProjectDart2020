#include "getdartsinputs.h"
#include <qvector.h>
#include <quuid.h>
#include <DartsModelsContext/Contracts/Input/idartsinput.h>
#include <DartsModelsContext/Contracts/Tournament/dartsmetamodel.h>
#include <DartsModelsContext/Contracts/Index/idartsindex.h>

GetDartsInputs::Model *GetDartsInputs::get(const DartsMetaModel &meta, const IDartsIndex *index, const Models &models) const
{
        for (const auto &model : models) {
                auto inputModel = dynamic_cast<IDartsInput*>(model);
                if(inputModel->tournamentId() != meta.tournamentId)
                        continue;
                else if(inputModel->playerId() != meta.playerId)
                        continue;
                else if(inputModel->roundIndex() != index->roundIndex())
                        continue;
                else if(inputModel->attempt() != index->attemptIndex())
                        continue;
                else
                        return model;
        }
        return nullptr;
}

GetDartsInputs::Models GetDartsInputs::get(const QUuid &tournamentId, const Models &models) const
{
        auto tournamentInputs = getModels(tournamentId,models);
        return tournamentInputs;
}

GetDartsInputs::Models GetDartsInputs::getHidden(const QUuid &tournamentId, const Models &models) const
{
        auto tournamentInputs = getModels(tournamentId,models);
        return getModels(HiddenHint,tournamentInputs);
}

GetDartsInputs::Models GetDartsInputs::getDisplayed(const QUuid &tournamentId, const Models &models) const
{
        auto tournamentInputs = getModels(tournamentId,models);
        return getModels(DisplayHint,tournamentInputs);
}

GetDartsInputs::Models GetDartsInputs::getModels(const QUuid &tournamentId, const Models &models) const
{
        Models list;
        for (const auto& model : models) {
                auto input = dynamic_cast<IDartsInput*>(model);
                if(input->tournamentId() == tournamentId)
                        list << input;
        }
        return list;
}

GetDartsInputs::Models GetDartsInputs::getModels(const int &hint, const Models &models) const
{
        Models list;
        for (const auto& model : models) {
                auto input = dynamic_cast<IDartsInput*>(model);
                if(input ->hint() == hint)
                        list << input;
        }
        return list;
}
