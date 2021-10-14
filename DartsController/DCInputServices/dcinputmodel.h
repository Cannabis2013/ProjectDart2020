#ifndef DCINPUTMODEL_H
#define DCINPUTMODEL_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
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
        int remainingScore() const override
        {
            return _totalScore;
        }
        void setTotalScore(const int& accumulatedScore) override
        {
            _totalScore = accumulatedScore;
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
    private:
        int _point = 0;
        int _modKeyCode;
        int _score = 0;
        int _totalScore = 0;
        QUuid _playerId;
        QString _playerName;
    };
}
#endif // DARTSPOINT_H
