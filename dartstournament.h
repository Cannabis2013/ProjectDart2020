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

        QVector<QUuid> assignedPlayerIds() const override
        {
            return _assignedPlayerIdentities;
        }
        DartsTournament* setAssignedPlayerIdentities(const QVector<QUuid> &playerIdentities) override
        {
            _assignedPlayerIdentities = playerIdentities;
            return this;
        }

        virtual QVector<QString> assignedPlayerNames() const override
        {
            return _assignedPlayerNames;
        }

        virtual ITournament *setAssignedPlayerNames(const QVector<QString> &names) override
        {
            _assignedPlayerNames = names;
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
            obj["terminalKeyCode"] = _terminalKeyCode;
            QJsonArray arr1;
            for (const auto& assignedPlayerId : _assignedPlayerIdentities)
                arr1 << assignedPlayerId.toString(QUuid::WithoutBraces);
            obj["assignedPlayerIds"] = arr1;
            QJsonArray arr2;
            for (const auto &assignedPlayerName : _assignedPlayerNames)
                arr2 << assignedPlayerName;
            obj["assignedPlayerNames"] = arr2;
            auto json = QJsonDocument(obj).toJson();
            return json;
        }
    private:
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
        QVector<QString> _assignedPlayerNames;
    };
}


#endif // TOURNAMENT_H
