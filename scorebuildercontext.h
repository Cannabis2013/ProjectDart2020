#ifndef SCOREBUILDERCONTEXT_H
#define SCOREBUILDERCONTEXT_H

#include <quuid.h>
#include "iscoreparameter.h"
// ScoreBuilderCollection
namespace SBC {
    class FTPScoreParameters : public IScoreParameter
    {
    public:
        int pointValue;
        int scoreValue;
        int roundIndex;
        int setIndex;
        int attempt;
        int hint;
        int keyCode;
        int gameMode;
        QUuid playerId;
        QUuid tournament;
        QUuid id;
        virtual int parentGameMode() const override
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

#endif // SCOREBUILDERCONTEXT_H
