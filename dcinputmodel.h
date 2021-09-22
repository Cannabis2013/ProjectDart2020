#ifndef DCINPUTMODEL_H
#define DCINPUTMODEL_H

#include "DCInputsSLA/idcinputmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DCContext
{
    class DCInputModel : public IDCInputModel
    {
    public:
        static DCInputModel* createInstance()
        {
            return new DCInputModel();
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        void setPlayerId(const QUuid &newPlayerId) override
        {
            _playerId = newPlayerId;
        }
        virtual QString playerName() const override
        {
            return _playerName;
        }
        virtual void setPlayerName(const QString &name) override
        {
            _playerName = name;
        }
        int totalScore() const override
        {
            return _accumulatedScore;
        }
        void setTotalScore(const int& accumulatedScore) override
        {
            _accumulatedScore = accumulatedScore;
        }
        int point() const override
        {
            return _point;
        }
        void setPoint(const int& newPoint) override
        {
            _point = newPoint;
        }
        int score() const override
        {
            return _score;
        }
        void setScore(const int &score) override
        {
            _score = score;
        }
        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        void setModKeyCode(const int& newModKeyCode) override
        {
            _modKeyCode = newModKeyCode;
        }
        virtual QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        virtual void setTournamentId(const QUuid &id) override
        {
            _tournamentId = id;
        }
    private:
        int _point;
        int _modKeyCode;
        int _score;
        int _accumulatedScore;
        QUuid _playerId, _tournamentId;
        QString _playerName;
    };
}
#endif // DARTSPOINT_H
