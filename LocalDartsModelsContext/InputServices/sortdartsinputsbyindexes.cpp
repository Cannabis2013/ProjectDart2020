#include "sortdartsinputsbyindexes.h"
#include <DartsModelsContext/InputModelsSLAs/idartsinput.h>

bool SortDartsInputsByIndexes::operator ()(const IModel<QUuid> *_first, const IModel<QUuid> *_second) const
{
        auto firstModel = dynamic_cast<const IDartsInput*>(_first);
        auto secondModel = dynamic_cast<const IDartsInput*>(_second);
        if(firstModel->roundIndex() < secondModel->roundIndex())
                return true;
        else if(secondModel->roundIndex() >= secondModel->roundIndex())
                return false;
        else if(firstModel->playerIndex() < secondModel->playerIndex())
                return true;
        else if(firstModel->playerIndex() > secondModel->playerIndex())
                return false;
        else if(firstModel->attempt() < secondModel->attempt())
                return true;
        else
                return false;
}
