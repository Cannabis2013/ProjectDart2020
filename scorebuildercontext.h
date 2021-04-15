#ifndef SCOREBUILDERCONTEXT_H
#define SCOREBUILDERCONTEXT_H

#include <quuid.h>
#include "iscoreparameter.h"
// ScoreBuilderCollection
namespace SBC {
    class FtpScoreParameters : public IScoreParameter
    {
    public:
        int pointValue;
        int scoreValue;
        int accumulatedScoreValue;
        int roundIndex;
        int setIndex;
        int attempt;
        int hint;
        int keyCode;
        QUuid playerId;
        QUuid tournament;
        QUuid id;
        virtual int parentGameMode() const override
        {
            return -1;
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
