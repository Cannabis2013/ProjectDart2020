#ifndef DARTSTOURNAMENT_H
#define DARTSTOURNAMENT_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>
#include "idartstournament.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsModelsContext{
    class DartsTournament : public IDartsTournament
    {
    public:
        static DartsTournament * createInstance()
        {
            return new DartsTournament();
        }
        static DartsTournament* fromJson(const QByteArray& json,
                                               const bool& generateId = false)
        {
            auto document = QJsonDocument::fromJson(json);
            auto model = new DartsTournament(document.object());
            if(generateId)
                model->setId(QUuid::createUuid());
            return model;
        }
        static DartsTournament* fromJsonObject(const QJsonObject& jsonObject,
                                               const bool& generateId = false)
        {
            auto model = new DartsTournament(jsonObject);
            if(generateId)
                model->setId(QUuid::createUuid());
            return model;
        }
        QUuid id() const override
        {
            return _id;
        }
        DartsTournament* setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        QString title() const override
        {
            return _title;
        }
        DartsTournament* setTitle(const QString &string) override
        {
            _title = string;
            return this;
        }
        int attempts() const override
        {
            return _attempts;
        }
        DartsTournament* setAttempts(const int &val) override
        {
            _attempts = val;
            return this;
        }
        int gameMode() const override
        {
            return _gameMode;
        }
        DartsTournament* setGameMode(const int &val) override
        {
            _gameMode = val;
            return this;
        }
        int keyPoint() const override
        {
            return _keyPoint;
        }
        DartsTournament* setKeyPoint(const int &val) override
        {
            _keyPoint = val;
            return this;
        }
        int status() const override
        {
            return _status;
        }
        DartsTournament* setStatus(const bool &status) override
        {
            _status = status;
            return this;
        }
        QUuid winnerId() const override
        {
            return _winnerId;
        }
        DartsTournament* setWinnerId(const QUuid &val) override
        {
            _winnerId = val;
            return this;
        }

        QVector<QUuid> assignedPlayerIdentities() const override
        {
            return _assignedPlayerIdentities;
        }
        DartsTournament* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
        {
            _assignedPlayerIdentities = playerIdentities;
            return this;
        }
        DartsTournament* assignPlayerIdentity(const QUuid &identity) override
        {
            _assignedPlayerIdentities.append(identity);
            return this;
        }

        int terminalKeyCode() const override
        {
            return _terminalKeyCode;
        }
        DartsTournament* setTerminalKeyCode(const int &keyCode) override
        {
            _terminalKeyCode = keyCode;
            return this;
        }
        int displayHint() const override
        {
            return _displayHint;
        }

        DartsTournament* setDisplayHint(int modelDisplayHint) override
        {
            _displayHint = modelDisplayHint;
            return this;
        }
        int inputHint() const override
        {
            return _inputHint;
        }
        DartsTournament* setInputMode(const int &inputMode) override
        {
            _inputHint = inputMode;
            return this;
        }
        QByteArray toJson() const override
        {
            QJsonObject obj;
            obj["id"] = _id.toString(QUuid::WithoutBraces);
            obj["title"] = _title;
            obj["gameMode"] = _gameMode;
            obj["attempts"] = _attempts;
            obj["keyPoint"] = _keyPoint;
            obj["displayHint"] = _displayHint;
            obj["inputHint"] = _inputHint;
            obj["winnerId"] = _winnerId.toString(QUuid::WithoutBraces);
            QJsonArray arr;
            for (const auto& assignedPlayerId : _assignedPlayerIdentities) {
                arr << assignedPlayerId.toString(QUuid::WithoutBraces);
            }
            obj["assignedPlayerIds"] = arr;
            auto json = QJsonDocument(obj).toJson();
            return json;
        }

    private:
        DartsTournament(){}
        DartsTournament(const QJsonObject& jsonObject)
        {
            _id = QUuid::fromString(jsonObject.value("id").toString());
            _title = jsonObject.value("title").toString();
            _gameMode = jsonObject.value("gameMode").toInt();
            _keyPoint = jsonObject.value("keyPoint").toInt();
            _attempts = jsonObject.value("attempts").toInt();
            _terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
            _displayHint = jsonObject.value("displayHint").toInt();
            _inputHint = jsonObject.value("inputHint").toInt();
            _status = jsonObject.value("status").toInt();
            _winnerId = QUuid::fromString(jsonObject.value("winnerId").toString(""));
            auto arr = jsonObject.value("assignedPlayerIds").toArray();
            for (const auto& jsonValue : arr) {
                auto stringId = jsonValue.toString();
                auto id = QUuid::fromString(stringId);
                _assignedPlayerIdentities << id;
            }
        }
        QString _title;
        int _attempts;
        int _gameMode;
        int _keyPoint;
        int _status;
        int _terminalKeyCode;
        int _displayHint;
        int _inputHint;
        QUuid _id;
        QUuid _winnerId;
        QVector<QUuid> _assignedPlayerIdentities;
    };
}


#endif // TOURNAMENT_H
