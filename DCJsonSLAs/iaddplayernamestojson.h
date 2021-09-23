#ifndef IADDPLAYERNAMESTOJSON_H
#define IADDPLAYERNAMESTOJSON_H

#include "DCInputSLAs/idcinputmodel.h"
#include <qvector.h>
#include "DCInputSLAs/idcinputmodel.h"
#include "DCPlayerSLAs/idcplayer.h"
#include "DCScoresSLAs/idcscoresservice.h"
#include "DCInputSLAs/idcinputjsonkeys.h"
class IAddPlayerNamesToJson
{
public:
    virtual void addPlayerNamesToJson(QByteArray &json, IDCScoresService* scoresService, const IDCInputJsonKeys *keys) const = 0;
};
#endif // IADDPLAYERNAMESTOJSONENTITY_H
