#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <quuid.h>
#include <qvector.h>

struct FTPParameters
{
    int attempts;
    int gameMode;
    int initialPoint;
    int status;
    int modelTableViewHint;
    int inputMode;
    int tournamentsCount = 0;
    int winConditionKey = 0x2B;
    QUuid id;
    QString title;
    QUuid winner;
    QVector<QUuid> playerIdentities;
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
