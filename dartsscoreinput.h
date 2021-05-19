#ifndef DARTSSCOREINPUT_H
#define DARTSSCOREINPUT_H

#include <quuid.h>
#include "idartsscoreinput.h"
namespace DartsModelsContext {
    class DartsScoreInput : public IDartsScoreInput
    {
    public:
        static DartsScoreInput* createInstance()
        {
            return new DartsScoreInput();
        }
        QUuid id() const override
        {
            return _id;
        }
        DartsScoreInput *setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        int hint() const override
        {
            return _hint;
        }
        DartsScoreInput *setHint(const int &hint) override
        {
            _hint = hint;
            return this;
        }
        QUuid playerId() const override
        {
            return _player;
        }
        DartsScoreInput *setPlayer(const QUuid &id) override
        {
            _player = id;
            return this;
        }
        QUuid tournamentId() const override
        {
            return _tournament;
        }
        DartsScoreInput *setTournamentId(const QUuid &tournamentId) override
        {
            _tournament = tournamentId;
            return this;
        }
        int roundIndex() const override
        {
           return _roundIndex;
        }
        DartsScoreInput *setRoundIndex(const int &index) override
        {
            _roundIndex = index;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsScoreInput *setSetIndex(const int &index) override
        {
            _setIndex = index;
            return this;
        }
        int score() const override
        {
            return _score;
        }
        DartsScoreInput *setScore(const int &score) override
        {
            _score = score;
            return this;
        }
    private:
        int _score;
        int _roundIndex;
        int _setIndex;
        int _hint;
        QUuid _id;
        QUuid _player;
        QUuid _tournament;
    };
}


#endif // DARTSSCOREINPUT_H
