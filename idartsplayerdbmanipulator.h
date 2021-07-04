#ifndef IDARTSPLAYERDBMANIPULATOR_H
#define IDARTSPLAYERDBMANIPULATOR_H

#include "iplayerdbmanipulator.h"

#include "iplayermodel.h"
#include "iplayermodelsdb.h"

class IDartsPlayerDbManipulator : public IPlayerDbManipulator<DartsModelsContext::IPlayerModel,QUuid, IPlayerModelsDb>
{};

#endif // IDARTSPLAYERDBMANIPULATOR_H
