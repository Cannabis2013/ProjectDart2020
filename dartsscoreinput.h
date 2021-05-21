#ifndef DARTSSCOREINPUT_H
#define DARTSSCOREINPUT_H

#include <quuid.h>
#include "idartsscoreinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsModelsContext {
    class DartsScoreInput : public IDartsScoreInput
    {
    public:
        static DartsScoreInput* createInstance()
        {
            return new DartsScoreInput();
        }
        static DartsScoreInput* createInstance(const QByteArray& json,
                                               const bool& generateId = false)
        {
            auto model = new DartsScoreInput(json);
            if(generateId)
                model->setId(QUuid::createUuid());
            return model;
        }
        static DartsScoreInput* createInstance(const QJsonObject& jsonObject,
                                               const bool& generateId = false)
        {
            auto model = new DartsScoreInput(jsonObject);
            if(generateId)
                model->setId(QUuid::createUuid());
            return model;
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
            return _playerId;
        }
        DartsScoreInput *setPlayerId(const QUuid &id) override
        {
            _playerId = id;
            return this;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        DartsScoreInput *setPlayerName(const QString &name) override
        {
            _playerName = name;
            return this;
        }
        QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        DartsScoreInput *setTournamentId(const QUuid &tournamentId) override
        {
            _tournamentId = tournamentId;
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
        QByteArray toJson() const override
        {
            QJsonObject jsonObject;
            jsonObject["score"] = _score;
            jsonObject["roundIndex"] = _roundIndex;
            jsonObject["setIndex"] = _setIndex;
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
        DartsScoreInput()
        {
        }
        DartsScoreInput(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            _score = jsonObject.value("score").toInt();
            _roundIndex = jsonObject.value("roundIndex").toInt();
            _setIndex = jsonObject.value("setIndex").toInt();
            _hint = jsonObject.value("hint").toInt();
            _playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            _playerName = jsonObject.value("playerName").toString();
            _tournamentId = QUuid::fromString(jsonObject.value("tournamentId").toString());
            _id = QUuid::fromString(jsonObject.value("id").toString(""));
        }
        DartsScoreInput(const QJsonObject& jsonObject)
        {
            _score = jsonObject.value("score").toInt();
            _roundIndex = jsonObject.value("roundIndex").toInt();
            _setIndex = jsonObject.value("setIndex").toInt();
            _hint = jsonObject.value("hint").toInt();
            _playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            _playerName = jsonObject.value("playerName").toString();
            _tournamentId = QUuid::fromString(jsonObject.value("tournamentId").toString());
            _id = QUuid::fromString(jsonObject.value("id").toString(""));
        }
        int _score;
        int _roundIndex;
        int _setIndex;
        int _hint;
        QUuid _id;
        QUuid _playerId;
        QString _playerName;
        QUuid _tournamentId;
    };
}


#endif // DARTSSCOREINPUT_H
