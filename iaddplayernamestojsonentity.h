#ifndef IADDPLAYERNAMESTOJSONENTITY_H
#define IADDPLAYERNAMESTOJSONENTITY_H

#include "idpcmodel.h"
#include <qvector.h>
#include "idpcmodel.h"
#include "idcplayer.h"
#include "idcscoresservice.h"
class IAddPlayerNamesToJsonEntity
{
public:
    virtual void addPlayerNamesToJson(QByteArray &json, const IDCScoresService* scoresService) const = 0;
};
#endif // IADDPLAYERNAMESTOJSONENTITY_H
