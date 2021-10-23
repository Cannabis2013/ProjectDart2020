#ifndef DARTSMETAMODEL_H
#define DARTSMETAMODEL_H

#include <quuid.h>
#include <QString>

struct DartsMetaModel
{
    QUuid playerId;
    QString playerName;
    QUuid tournamentId;
};

#endif // DARTSMETAMODEL_H
