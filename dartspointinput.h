#ifndef POINT_H
#define POINT_H

#include "idartspointinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsModelsContext{
    class DartsPointInput : public IDartsPointInput
    {
    public:
        static DartsPointInput* createInstance()
        {
            return new DartsPointInput();
        }
        static DartsPointInput* fromJson(const QByteArray& json,
                                         const int& hint = -1,
                                         const bool& generateId = false)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto model = new DartsPointInput(jsonObject);
            if(generateId)
                model->setId(QUuid::createUuid());
            if(hint != -1)
                model->setHint(hint);
            return model;
        }
        static DartsPointInput* fromJsonObject(const QJsonObject& jsonObject,
                                               const bool& generateId = false)
        {
            auto model = new DartsPointInput(jsonObject);
            if(generateId)
                model->setId(QUuid::createUuid());
            return model;
        }
        QUuid id() const override
        {
            return _id;
        }
        DartsPointInput* setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        int point() const override
        {
            return _point;
        }
        DartsPointInput* setPoint(const int &point) override
        {
            _point = point;
            return this;
        }
        int score() const override
        {
            return _score;
        }
        DartsPointInput *setScore(const int& score) override
        {
            _score = score;
            return this;
        }

        QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        DartsPointInput* setTournamentId(const QUuid &id) override
        {
            _tournamentId = id;
            return this;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        DartsPointInput* setPlayerId(const QUuid &id) override
        {
            _playerId = id;
            return this;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        DartsPointInput *setPlayerName(const QString &name) override
        {
            _playerName = name;
            return this;
        }
        int attempt() const override
        {
            return _attempt;
        }
        DartsPointInput* setAttempt(const int &index) override
        {
            _attempt = index;
            return this;
        }
        int hint() const override
        {
            return _hint;
        }
        DartsPointInput* setHint(const int &hint) override
        {
            _hint = hint;
            return this;
        }

        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        DartsPointInput* setModKeyCode(const int &key) override
        {
            _modKeyCode = key;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsPointInput* setSetIndex(const int &index) override
        {
            _setIndex = index;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DartsPointInput* setRoundIndex(const int &index) override
        {
            _roundIndex = index;
            return this;
        }
        QUuid tournament() const
        {
            return _tournamentId;
        }
        DartsPointInput* setTournament(const QUuid &tournament)
        {
            _tournamentId = tournament;
            return this;
        }
        QByteArray toJson() const override
        {
            QJsonObject jsonObject;
            jsonObject["point"] = _point;
            jsonObject["score"] = _score;
            jsonObject["modKeyCode"] = _modKeyCode;
            jsonObject["roundIndex"] = _roundIndex;
            jsonObject["setIndex"] = _setIndex;
            jsonObject["attempt"] = _attempt;
            jsonObject["hint"] = _hint;
            jsonObject["id"] = _id.toString(QUuid::WithoutBraces);
            jsonObject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonObject["playerName"] = _playerName;
            jsonObject["tournamentId"] = _tournamentId.toString(QUuid::WithoutBraces);
            auto document = QJsonDocument(jsonObject);
            auto json = document.toJson();
            return json;
        }
    private:
        DartsPointInput()
        {
        }
        DartsPointInput(const QJsonObject& jsonObject)
        {
            _point = jsonObject.value("point").toInt();
            _modKeyCode = jsonObject.value("modKeyCode").toInt();
            _score = jsonObject.value("score").toInt();
            _roundIndex = jsonObject.value("roundIndex").toInt();
            _setIndex = jsonObject.value("setIndex").toInt();
            _attempt = jsonObject.value("attempt").toInt();
            _hint = jsonObject.value("hint").toInt();
            _playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            _playerName = jsonObject.value("playerName").toString();
            _tournamentId = QUuid::fromString(jsonObject.value("tournamentId").toString());
            _id = QUuid::fromString(jsonObject.value("id").toString(""));
        }

        int _point;
        int _score;
        int _roundIndex;
        int _setIndex;
        int _attempt;
        int _hint;
        int _modKeyCode;
        QUuid _id;
        QUuid _playerId;
        QString _playerName;
        QUuid _tournamentId;
    };
};
#endif // POINT_H
