#ifndef DARTSPOINTTURNVALUES_H
#define DARTSPOINTTURNVALUES_H

#include <qstring.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DPCContext {
    class DartsPointTurnValues
    {
    public:
        bool getCanUndo() const
        {
            return _canUndo;
        }
        void setCanUndo(bool newCanUndo)
        {
            _canUndo = newCanUndo;
        }
        bool getCanRedo() const
        {
            return _canRedo;
        }
        void setCanRedo(bool newCanRedo)
        {
            _canRedo = newCanRedo;
        }
        int getRoundIndex() const
        {
            return _roundIndex;
        }
        void setRoundIndex(int newRoundIndex)
        {
            _roundIndex = newRoundIndex;
        }
        int getSetIndex() const
        {
            return _setIndex;
        }
        void setSetIndex(int newSetIndex)
        {
            _setIndex = newSetIndex;
        }
        int getAttemptIndex() const
        {
            return _attemptIndex;
        }
        void setAttemptIndex(int newAttemptIndex)
        {
            _attemptIndex = newAttemptIndex;
        }
        const QString &getTargetRow() const
        {
            return _targetRow;
        }
        void setTargetRow(const QString &newTargetRow)
        {
            _targetRow = newTargetRow;
        }
        const QString &getPlayerName() const
        {
            return _playerName;
        }
        void setPlayerName(const QString &newPlayerName)
        {
            _playerName = newPlayerName;
        }
        QByteArray toJson() const
        {
            QJsonObject jsonObject;
            jsonObject["roundIndex"] = _roundIndex;
            jsonObject["setIndex"] = _setIndex;
            jsonObject["attemptIndex"] = _attemptIndex;
            jsonObject["canUndo"] = _canUndo;
            jsonObject["canRedo"] = _canRedo;
            jsonObject["currentPlayerName"] = _playerName;
            jsonObject["targetRow"] = _targetRow;
            auto document = QJsonDocument(jsonObject);
            auto json = document.toJson();
            return json;
        }
    private:
       bool _canUndo;
       bool _canRedo;
       int _roundIndex;
       int _setIndex;
       int _attemptIndex;
       QString _targetRow;
       QString _playerName;
    };
}

#endif // DARTSPOINTTURNVALUES_H
