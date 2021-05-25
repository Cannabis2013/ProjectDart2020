#ifndef POINTINDEXCONTROLLER_H
#define POINTINDEXCONTROLLER_H

#include "idartssingleattemptindexservice.h"
#include <qlist.h>
#include "idartssingleattemptindexes.h"

namespace DartsPointSingleAttemptContext{
    class PointIndexController : public IDartsSingleAttemptIndexService<IDartsSingleAttemptIndexes>
    {
        // IndexControllerInterface interface
    public:
        static PointIndexController* createInstance(const int &attemptCount)
        {
            return new PointIndexController(attemptCount);
        }

        virtual void setIndexes(const IDartsSingleAttemptIndexes* indexes) override
        {
            _totalIndex = indexes->totalTurns();
            _turnIndex = indexes->turnIndex();
            _roundIndex = indexes->roundIndex();
            _setIndex = indexes->setIndex();
            _attemptIndex = indexes->attemptIndex();
        }

        virtual void reset() override
        {
            _totalIndex = 0;
            _turnIndex = 0;
            _roundIndex = 1;
            _setIndex = 0;
            _attemptIndex = 0;
        }

        virtual void next() override
        {
            incrementTurnIndex();
            if(isLastAttempt())
            {
                incrementSetIndex();
                resetLegIndex();
                if(setIndex() >= playerCount()){
                    incrementRoundIndex();
                    resetSetIndex();
                }
            }
            else
            {
                incrementLegIndex();
            }
        }
        virtual void undo() override
        {
            _turnIndex--;
            if(attemptIndex() > 0)
               _attemptIndex--;
            else
            {
                _attemptIndex = 2;

                if(setIndex() == 0)
                {
                    _setIndex = lastPlayerIndex();
                    _roundIndex--;
                }
                else
                {
                    _setIndex--;
                }
            }
        }
        virtual void redo() override
        {
            if(++_attemptIndex >= _numberOfAttempts)
            {
                _attemptIndex = 0;
                if(_setIndex == lastPlayerIndex())
                {
                    _setIndex = 0;
                    _roundIndex++;
                }
                else
                    _setIndex++;
            }
            _turnIndex++;
        }
        virtual bool canUndo() const override
        {
            return turnIndex() > 0;
        }
        virtual bool canRedo() const override
        {
            return turnIndex() < _totalIndex;
        }
        virtual void syncIndex() override
        {
            _totalIndex = _turnIndex;
        }
        virtual int turnIndex() const override
        {
            return _turnIndex;
        }
        virtual void setTurnIndex(const int &index) override
        {
            _turnIndex = index;
        }
        virtual int totalIndex() const override
        {
            return _totalIndex;
        }
        virtual void setTotalIndex(const int &index) override
        {
            _totalIndex = index;
        }
        virtual int roundIndex() const override
        {
            return _roundIndex;
        }
        void setRoundIndex(const int& roundIndex) override
        {
            _roundIndex = roundIndex;
        }
        virtual int setIndex() const override
        {
            return _setIndex;
        }
        void setSetIndex(const int& setIndex) override
        {
            _setIndex = setIndex;
        }
        virtual int attemptIndex() const override
        {
            return _attemptIndex;
        }

        virtual void setAttempt(const int &index) override
        {
            _attemptIndex = index;
        }
        int numberOfAttempts() const override
        {
            return _numberOfAttempts;
        }
        void setNumberOfAttempts(const int& numberOfAttempts) override
        {
            _numberOfAttempts = numberOfAttempts;
        }
        virtual int playersCount() const override
        {
            return _playersCount;
        }
        virtual void setPlayersCount(const int &count) override
        {
            _playersCount = count;
        }
    private:
        PointIndexController(const int &attempts) :
            _numberOfAttempts(attempts)
        {}
        int playerCount()
        {
            return _playersCount;
        }
        void incrementTurnIndex()
        {
            if(_turnIndex == _totalIndex)
                _totalIndex++;
            _turnIndex++;
        }

        int isLastAttempt()
        {
            auto result = _turnIndex % _numberOfAttempts == 0;
            return result;
        }
        void incrementRoundIndex()
        {
            _roundIndex++;
        }
        void incrementSetIndex()
        {
            _setIndex++;
        }
        void incrementLegIndex()
        {
            _attemptIndex++;
        }
        void resetSetIndex()
        {
            _setIndex = 0;
        }
        void resetLegIndex()
        {
            _attemptIndex = 0;
        }

        int lastPlayerIndex()
        {
            return playerCount() -1;
        }

        int _turnIndex = 0, _totalIndex  = 0, _roundIndex = 1, _setIndex = 0, _attemptIndex = 0;
        int _numberOfAttempts, _playersCount;
    };
}

#endif // POINTINDEXCONTROLLER_H
