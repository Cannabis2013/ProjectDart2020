#ifndef DSCMODEL_H
#define DSCMODEL_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include "idscmodel.h"

namespace DSCContext
{
    class DSCModel : public IDSCModel
    {
    public:
        static DSCModel* createInstance()
        {
            return new DSCModel;
        }

        int score() const override
        {
            return _score;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        void setPlayerId(const QUuid &newPlayerId) override
        {
            _playerId = newPlayerId;
        }
        void setPlayerName(const QString &newPlayerName) override
        {
            _playerName = newPlayerName;
        }
        void setScore(int newScore) override
        {
            _score = newScore;
        }
        virtual QByteArray toJson() const override
        {
            QJsonObject jsonobject;
            jsonobject["score"] = _score;
            jsonobject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonobject["playerName"] = _playerName;
            jsonobject["totalScore"] = _accumulatedScore;
            auto document = QJsonDocument(jsonobject);
            auto json = document.toJson();
            return json;
        }
        int totalScore() const override
        {
            return _accumulatedScore;
        }
        void setTotalScore(const int& accumulatedScore) override
        {
            _accumulatedScore = accumulatedScore;
        }
        Id tournamentId() const override
        {
            return _tournamentId;
        }
        void setTournamentId(const Id &id) override
        {
            _tournamentId = id;
        }
    private:
        int _score;
        int _accumulatedScore;
        QUuid _playerId;
        QString _playerName;
        QUuid _tournamentId;
    };
};

#endif // DARTSSCORE_H
