#ifndef DARTSINDEXES_H
#define DARTSINDEXES_H

#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"

namespace ModelsContext{
    class DartsIndexes : public IDartsIndexes
    {
    public:
        static DartsIndexes* createInstance()
        {
            return new DartsIndexes;
        }
        static const DartsIndexes* createInitialInstance()
        {
            auto indexes = DartsIndexes::createInstance();
            indexes->setTotalTurns(0);
            indexes->setTurnIndex(0);
            indexes->setRoundIndex(1);
            indexes->setSetIndex(0);
            indexes->setAttemptIndex(0);
            return indexes;
        }
        int totalTurns() const override
        {
            return _totalTurns;
        }
        void setTotalTurns(const int& val) override
        {
            _totalTurns = val;
        }
        int turnIndex() const override
        {
            return _turnIndex;
        }
        void setTurnIndex(const int& val) override
        {
            _turnIndex = val;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        void setRoundIndex(const int& val) override
        {
            _roundIndex = val;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        void setSetIndex(const int& val) override
        {
            _setIndex = val;
        }
        int attemptIndex() const override
        {
            return _attemptIndex;
        }
        void setAttemptIndex(const int& val) override
        {
            _attemptIndex = val;
        }
    private:
        int _totalTurns;
        int _turnIndex;
        int _roundIndex;
        int _setIndex;
        int _attemptIndex;
    };
}


#endif // DARTSPOINTINDEXES_H
