#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
        DartsPlayer() { }

        DartsPlayer(const QString& name)
            : _name(name)
        {
        }

        DartsPlayer(const QString& name, const QString& url, const QString& nationality)
            : _name(name)
            , _winnerImageUrl(url)
            , _nationality(nationality)
        {
        }

        DartsPlayer(const QJsonObject& jsonObj)
        {
                _name = jsonObj.value("name").toString("");
                _winner = jsonObj.value("winner").toBool();
                _winnerImageUrl = jsonObj.value("winnerImage").toString("");
        }

        QJsonObject jsonObject() const
        {
                QJsonObject jsonObj;
                jsonObj["name"] = _name;
                jsonObj["winner"] = _winner;
                jsonObj["winnerImage"] = _winnerImageUrl;
                jsonObj["nationality"] = _nationality;
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
        QString _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png";
        QString _nationality = "";
        bool _winner = false;
};

#endif // DARTSPLAYER_H
