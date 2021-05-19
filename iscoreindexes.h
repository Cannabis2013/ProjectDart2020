#ifndef ISCOREINDEXES_H
#define ISCOREINDEXES_H

namespace DartsScoreMultiAttemptContext {
    class IScoreIndexes
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
    };
}

#endif // ISCOREINDEXES_H
