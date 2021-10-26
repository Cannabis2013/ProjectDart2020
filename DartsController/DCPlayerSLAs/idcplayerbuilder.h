#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include "DartsController/DCPlayerServices/dcplayer.h"
#include <qvector.h>
#include "DartsController/DCInputServices/dcinput.h"

class IDCPlayerBuilder
{
public:
    virtual DCPlayer createPlayer(const DCInput &input) const = 0;
    virtual DCPlayer createWinner(const QByteArray &json) const = 0;
    virtual QVector<DCPlayer> createPlayers(const QByteArray &json) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
