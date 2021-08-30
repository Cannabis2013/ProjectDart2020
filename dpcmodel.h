#ifndef DPCMODEL_H
#define DPCMODEL_H

#include "idpcmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DPCContext
{
    class DPCModel : public IDPCModel
    {
    public:
        static DPCModel* createInstance()
        {
            return new DPCModel();
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
    private:
        int _point;
        int _modKeyCode;
        int _score;
        int _accumulatedScore;
        QUuid _playerId;
        QString _playerName;
    };
}
#endif // DARTSPOINT_H
