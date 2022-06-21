#ifndef DARTSINPUT_H
#define DARTSINPUT_H
#include <quuid.h>

#include <DartsModelsContext/Contracts/Input/idartsinput.h>

class DartsInput : public IDartsInput
{
public:
    QUuid id() const override
    {
        return _id;
    }
    void setId(const QUuid &val) override
    {
        _id = val;
    }
    int point() const override
    {
        return _point;
    }
    void setPoint(const int &point) override
    {
        _point = point;
    }
    int score() const override
    {
        return _score;
    }
    void setScore(const int& score) override
    {
        _score = score;
    }

    QUuid tournamentId() const override
    {
        return _tournamentId;
    }
    void setTournamentId(const QUuid &id) override
    {
        _tournamentId = id;
    }
    QUuid playerId() const override
    {
        return _playerId;
    }
    void setPlayerId(const QUuid &id) override
    {
        _playerId = id;
    }
    QString playerName() const override
    {
        return _playerName;
    }
    void setPlayerName(const QString &name) override
    {
        _playerName = name;
    }
    int attempt() const override
    {
        return _attempt;
    }
    void setAttempt(const int &index) override
    {
        _attempt = index;
    }
    int hint() const override
    {
        return _hint;
    }
    void setHint(const int &hint) override
    {
        _hint = hint;
    }
    int modKeyCode() const override
    {
        return _modKeyCode;
    }
    void setModKeyCode(const int &key) override
    {
        _modKeyCode = key;
    }
    int playerIndex() const override
    {
        return _setIndex;
    }
    void setPlayerIndex(const int &index) override
    {
        _setIndex = index;
    }
    int roundIndex() const override
    {
        return _roundIndex;
    }
    void setRoundIndex(const int &index) override
    {
        _roundIndex = index;
    }
    int remainingScore() const override
    {
        return _remainingScore;
    }
    void setRemainingScore(const int &score) override
    {
        _remainingScore = score;
    }
    bool inGame() const override
    {
        return _inGame;
    }
    void setInGame(const bool &value) override
    {
        _inGame = value;
    }
    bool approved() const override
    {
        return _approved;
    }
    void setApproved(const bool &val) override
    {
        _approved = val;
    }
private:
    QUuid _id;
    QUuid _tournamentId;
    int _hint;
    int _point = 0;
    int _score = 0;
    int _roundIndex = 0;
    int _setIndex = 0;
    int _attempt = 0;
    int _modKeyCode;
    int _remainingScore;
    bool _inGame = false;
    bool _approved = false;
    QUuid _playerId;
    QString _playerName;
};
#endif // POINT_H
