#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include "DartsController/DCPlayerServices/dcplayer.h"
#include <qvector.h>

class IDCPlayerBuilder
{
public:
    virtual DCPlayer createModel(const QUuid &id, const QString &name) const = 0;
    virtual QVector<DCPlayer> createPlayers(const QByteArray &json) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
