#ifndef DARTSTOURNAMENT_H
#define DARTSTOURNAMENT_H
#include <quuid.h>
#include <qvector.h>
#include "TournamentModelsSLAs/idartstournament.h"
class DartsTournament : public IDartsTournament
{
public:
    int initialRemaining() const override {return _keyPoint;}
    void setKeyPoint(const int &val) override {_keyPoint = val;}
    int inputHint() const override {return _inputHint;}
    void setInputHint(const int &inputMode) override {_inputHint = inputMode;}
    QVector<QUuid> playerIds() const override {return _ids;}
    void setPlayerIds(const QVector<QUuid> &playerIds) override {_ids = playerIds;}
    QVector<QString> playerNames() const override {return _names;}
    void setPlayerNames(const QVector<QString> &playerNames) override {_names = playerNames;}
    QUuid id() const override {return _id;}
    void setId(const QUuid &val) override {_id = val;}
    QString title() const override {return _title;}
    void setTitle(const QString &string) override {_title = string;}
    int gameMode() const override {return _gameMode;}
    void setGameMode(const int &val) override {_gameMode = val;}
    int status() const override {return _status;}
    void setStatus(const bool &active) override {_status = active;}
    QUuid winnerId() const override {return _winnerId;}
    void setWinnerId(const QUuid &val) override {_winnerId = val;}
    QString winnerName() const override {return _winnerName;}
    void setWinnerName(const QString &name) override {_winnerName = name;}
    int totalTurns() const override {return _totalTurns;}
    void setTotalTurns(const int& val) override {_totalTurns = val;}
    int turnIndex() const override {return _turnIndex;}
    void setTurnIndex(const int& val) override {_turnIndex = val;}
    int roundIndex() const override {return _roundIndex;}
    void setRoundIndex(const int& val) override {_roundIndex = val;}
    int setIndex() const override {return _setIndex;}
    void setSetIndex(const int& val) override {_setIndex = val;}
    int attemptIndex() const override {return _attemptIndex;}
    void setAttemptIndex(const int& val) override {_attemptIndex = val;}
private:
    int _keyPoint;
    int _inputHint;
    QVector<QUuid> _ids;
    QVector<QString> _names;
    QString _title;
    QUuid _id;
    QUuid _winnerId;
    QString _winnerName;
    int _status;
    int _gameMode;
    int _totalTurns = 0;
    int _turnIndex = 0;
    int _roundIndex = 0;
    int _setIndex = 0;
    int _attemptIndex = 0;
};
#endif // TOURNAMENT_H
