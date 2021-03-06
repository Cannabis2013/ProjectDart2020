#ifndef DARTSSCOREEXTENDED_H
#define DARTSSCOREEXTENDED_H

#include <qstring.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext {
    class DartsScoreTurnValues
    {
    public:

        int roundIndex() const
        {
            return _roundIndex;
        }
        void setRoundIndex(int newRoundIndex)
        {
            _roundIndex = newRoundIndex;
        }
        int setIndex() const
        {
            return _setIndex;
        }
        void setSetIndex(int newSetIndex)
        {
            _setIndex = newSetIndex;
        }
        int score() const
        {
            return _score;
        }
        void setScore(int newScore)
        {
            _score = newScore;
        }
        bool canUndo() const
        {
            return _canUndo;
        }
        void setCanUndo(bool newCanUndo)
        {
            _canUndo = newCanUndo;
        }
        bool canRedo() const
        {
            return _canRedo;
        }
        void setCanRedo(bool newCanRedo)
        {
            _canRedo = newCanRedo;
        }
        const QString &currentUserName() const
        {
            return _currentUserName;
        }
        void setCurrentUserName(const QString &newCurrentUserName)
        {
            _currentUserName = newCurrentUserName;
        }
        const QString &targetRow() const
        {
            return _targetRow;
        }
        void setTargetRow(const QString &newTargetRow)
        {
            _targetRow = newTargetRow;
        }

        QByteArray toJson() const
        {
            QJsonObject jsonObject;
            jsonObject["roundIndex"] = _roundIndex;
            jsonObject["setIndex"] = _setIndex;
            jsonObject["score"] = _score;
            jsonObject["canUndo"] = _canUndo;
            jsonObject["canRedo"] = _canRedo;
            jsonObject["playerName"] = _currentUserName;
            jsonObject["targetRow"] = _targetRow;
            auto document = QJsonDocument(jsonObject);
            auto json = document.toJson();
            return json;
        }

    private:
        int _roundIndex;
        int _setIndex;
        int _score;
        bool _canUndo;
        bool _canRedo;
        QString _currentUserName;
        QString _targetRow;
    };
}

#endif // DARTSSCOREEXTENDED_H
