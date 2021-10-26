#ifndef IADDPLAYERNAMESTOJSON_H
#define IADDPLAYERNAMESTOJSON_H

#include <qvector.h>
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
class IAddPlayerNamesToJson
{
public:
    virtual void addPlayerNamesToJson(QByteArray &json, IDCScoreModels *scoresService) const = 0;
};
#endif // IADDPLAYERNAMESTOJSONENTITY_H
