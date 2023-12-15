#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
        DartsPlayer() { }

        DartsPlayer(const QJsonObject& jsonObj)
        {
                _name = jsonObj.value("name").toString("");
                _winner = jsonObj.value("winner").toBool();
                _winnerImageUrl = jsonObj.value("winnerImage").toString("");
        }

        static DartsPlayer fromJson(QJsonObject& jsonObj)
        {
                DartsPlayer player;
                player._name = jsonObj["name"].toString("");
                player._winnerImageUrl = jsonObj["winnerImage"].toString("");
                return player;
        }

        QJsonObject toJsonObject() const
        {
                QJsonObject jsonObj;
                jsonObj["name"] = _name;
                jsonObj["winner"] = _winner;
                jsonObj["winnerImage"] = _winnerImageUrl;
                return jsonObj;
        }

        QString name() const
        {
                return _name;
        }
        bool winner() const
        {
                return _winner;
        }

        void setWinner(bool status)
        {
                _winner = status;
        }

        QString winnerImageUrl() const
        {
                return _winnerImageUrl;
        }

private:
        QString _name = "";
        QString _winnerImageUrl = "";
        bool _winner = false;
};

#endif // DARTSPLAYER_H
