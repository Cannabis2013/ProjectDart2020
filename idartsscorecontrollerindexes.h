#ifndef IDARTSSCORECONTROLLERINDEXES_H
#define IDARTSSCORECONTROLLERINDEXES_H

#include "ijson.h"

namespace DartsScoreControllerContext
{
    template<typename TJsonFormat>
    class IDartsScoreControllerIndexes : public IJson<TJsonFormat>
    {
    public:
        typedef TJsonFormat JsonFormat;
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual JsonFormat toJson() const override = 0;
    };
}

#endif // IDARTSMULTIATTEMPTINDEXES_H
