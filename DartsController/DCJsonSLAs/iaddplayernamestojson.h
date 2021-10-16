#ifndef IADDPLAYERNAMESTOJSON_H
#define IADDPLAYERNAMESTOJSON_H

#include "DartsController/DCInputSLAs/idcinput.h"
#include <qvector.h>
#include "DartsController/DCInputSLAs/idcinput.h"
#include "DartsController/DCPlayerSLAs/idcplayer.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
class IAddPlayerNamesToJson
{
public:
    virtual void addPlayerNamesToJson(QByteArray &json, IDCScoresService* scoresService) const = 0;
};
#endif // IADDPLAYERNAMESTOJSONENTITY_H
