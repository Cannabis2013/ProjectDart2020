#ifndef IDARTSMULTIATTEMPTINDEXES_H
#define IDARTSMULTIATTEMPTINDEXES_H
namespace DartsScoreControllerContext
{
    class IDartsMultiAttemptIndexes
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
    };
}

#endif // IDARTSMULTIATTEMPTINDEXES_H
