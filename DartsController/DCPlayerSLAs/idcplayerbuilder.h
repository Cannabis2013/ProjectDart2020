#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include "DartsController/DCPlayerServices/dcplayer.h"
#include <qvector.h>
#include "DartsController/DCInputServices/dcinput.h"

class IDCPlayerBuilder
{
public:
    virtual DCPlayer createPlayer(const DCInput &input) const = 0;
    virtual DCPlayer createWinner(const QJsonObject &obj) const = 0;
    virtual QVector<DCPlayer> createPlayers(const QJsonArray &obj) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
