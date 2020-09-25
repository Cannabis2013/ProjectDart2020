#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <quuid.h>
#include <qlist.h>

struct TournamentParameters
{
    int throws;
    int gameMode;
    int keyPoint;
    int status;
    QUuid winner;
    QUuid id;
    QString title;
    QList<QUuid> playerIdentities;

    QString defaultTitle = "Tournament";
    int defaultLegCount = 3;
    int defaultMaxPlayerCount = 24;
    int defaultKeyPoint = 501;
    int defaultGameMode = 0x0;
    int initialStatus = 0xc;
    int tournamentsCount = 0;
    int winConditionKey = 0x2B;
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
    char* t;
    int pointValue;
    int scoreValue;
    int throwIndex;
    int hint;
    int keyCode;
    QUuid playerId;
    QUuid setId;
    QUuid id;
};

struct ModelOptions
{
    bool generateUniqueId = true;
    bool customUuid = false;

    int modelHint = 0x9;
};

#endif // MODELBUILDERCONTEXT_H
