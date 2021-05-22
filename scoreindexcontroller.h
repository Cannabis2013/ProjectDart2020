#ifndef SCOREINDEXCONTROLLER_H
#define SCOREINDEXCONTROLLER_H

#include <qvector.h>
#include "idartsmultiattemptindexservice.h"
#include "idartsmultiattemptindexes.h"

namespace DartsScoreMultiAttemptContext
{
    class ScoreIndexController : public
            IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>
    {
    public:
        // Create instance
        static ScoreIndexController* createInstance();
        // IndexControllerInterface interface
        virtual void setIndexes(const IDartsMultiAttemptIndexes* indexes) override
        {
            _totalIndex = indexes->totalTurns();
            _turnIndex = indexes->turns();
            _roundIndex = indexes->roundIndex();
            _setIndex = indexes->setIndex();
        }
        virtual void reset() override;
        virtual void next() override;
        virtual void undo() override;
        virtual void redo() override;
        virtual bool canUndo() const override;
        virtual bool canRedo() const override;
        virtual void syncIndex() override;
        virtual int turnIndex() const override;
        virtual void setTurnIndex(const int &index) override
        {
            _turnIndex = index;
        }
        virtual int totalIndex() const override;
        virtual void setTotalIndex(const int &index) override
        {
            _totalIndex = index;
        }
        virtual int roundIndex() const override;
        virtual int setIndex() const override;

        void setPlayersCount(const int& playerCount) override;
        int playersCount()const override;

        virtual void setRoundIndex(const int &index) override;
        virtual void setSetIndex(const int &index) override;

        virtual int numberOfAttempts() const override;
        virtual void setNumberOfAttempts(const int &) override;
    private:
        // Private methods
        void incrementTurnIndex();
        void incrementRoundIndex();
        void incrementSetIndex();
        void resetSetIndex();
        void resetLegIndex();
        int lastPlayerIndex();

        int _turnIndex = 0;
        int _totalIndex  = 0;
        int _roundIndex = 1;
        int _setIndex = 0;
        int _attemptIndex = 0;
        int _playerCount;
    };
}


#endif // SCOREINDEXCONTROLLER_H
