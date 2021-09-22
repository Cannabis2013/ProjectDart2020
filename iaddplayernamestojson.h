#ifndef IADDPLAYERNAMESTOJSON_H
#define IADDPLAYERNAMESTOJSON_H

#include "DCInputsSLA/idcinputmodel.h"
#include <qvector.h>
#include "DCInputsSLA/idcinputmodel.h"
#include "idcplayer.h"
#include "idcscoresservice.h"
class IAddPlayerNamesToJson
{
public:
    virtual void addPlayerNamesToJson(QByteArray &json, IDCScoresService* scoresService) const = 0;
};
#endif // IADDPLAYERNAMESTOJSONENTITY_H
