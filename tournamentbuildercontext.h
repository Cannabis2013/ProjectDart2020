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
        QString title = "";
        QUuid winner;
        int gameMode = -1;
        int status = -1;
        int attempts = -1;
        int keyPoint = -1;
        int displayHint = -1;
        int inputHint = -1;
        int tournamentsCount = 0;
        int terminalKeyCode = 0x2B;
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
        bool useProvidedId = false;
    };
}

#endif // MODELBUILDERCONTEXT_H
