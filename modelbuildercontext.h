#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <quuid.h>
#include <qlist.h>

struct FTPParameters
{
    int throws;
    int gameMode;
    int keyPoint;
    int status;
    int modelTableViewHint;
    int inputMode;
    QUuid winner;
    QUuid id;
    QString title;
    QVector<QUuid> playerIdentities;

    QString defaultTitle = "Tournament";
    int defaultLegCount = 3;
    int defaultMaxPlayerCount = 24;
    int defaultKeyPoint = 501;
    int defaultGameMode = 0x0;
    int initialStatus = 0xc;
    int tournamentsCount = 0;
    int winConditionKey = 0x2B;
};

struct FTPScoreParameters
{
    int pointValue;
    int scoreValue;
    int roundIndex;
    int setIndex;
    int throwIndex;
    int hint;
    int keyCode;
    QUuid playerId;
    QUuid tournament;
    QUuid id;
};

struct ModelOptions
{
    bool generateUniqueId = true;
    bool customUuid = false;
};

#endif // MODELBUILDERCONTEXT_H
