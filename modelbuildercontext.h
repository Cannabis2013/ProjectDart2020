#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <qstring.h>
#include <quuid.h>
#include <qlist.h>

struct TournamentParameters
{
    QString title;
    int maxPlayers;
    int numberOfLegs;
    int gameMode;
    int keyPoint;
    int status;
    QUuid winner;
    QUuid id;
    QList<QUuid> playerIdentities;
};

struct RoundParameters
{
    int roundIndex;
    QUuid tournamentId;
    QUuid id;
};

struct SetParameters
{
    int index;
    QUuid roundId;
    QUuid id;
};

struct PointParameters
{
    int pointValue;
    int legIndex;
    QUuid playerId;
    QUuid setId;
    QUuid id;
};

struct ModelOptions
{
    bool generateUniqueId = true;
    bool customUuid = false;
};



#endif // MODELBUILDERCONTEXT_H
