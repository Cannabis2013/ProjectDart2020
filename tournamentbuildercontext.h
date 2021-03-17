#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <quuid.h>
#include <qvector.h>
#include "iscoreparameter.h"
#include "itournamentparameter.h"
namespace TBC {
    class FTPParameters : public ITournamentParameter
    {
    public:
        QUuid id;
        QString title;
        QUuid winner;
        int gameMode = -1;
        int status;
        int attempts = -1;
        int keyPoint = -1;
        int modelTableViewHint;
        int inputMode;
        int tournamentsCount = 0;
        int winConditionKey = 0x2B;
        QVector<QUuid> playerIdentities;
        int tournamentGameMode() const override
        {
            return gameMode;
        }
    };
    class ModelOptions
    {
    public:
        bool generateUniqueId = true;
        bool customUuid = false;
    };
}

#endif // MODELBUILDERCONTEXT_H
