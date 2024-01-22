#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
        DartsPlayer() { }

<<<<<<< Updated upstream
=======
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

>>>>>>> Stashed changes
        DartsPlayer(const QJsonObject& jsonObj)
        {
                _name = jsonObj.value("name").toString("");
                _winner = jsonObj.value("winner").toBool();
                _winnerImageUrl = jsonObj.value("winnerImage").toString("");
        }

<<<<<<< Updated upstream
        static DartsPlayer fromJson(QJsonObject& jsonObj)
        {
                DartsPlayer player;
                player._name = jsonObj["name"].toString("");
                player._winnerImageUrl = jsonObj["winnerImage"].toString("");
                return player;
        }

=======
>>>>>>> Stashed changes
        QJsonObject toJsonObject() const
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

protected:
        QString _name = "";
<<<<<<< Updated upstream
        QString _winnerImageUrl = "";

private:
=======
        QString _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png";
        QString _nationality = "";
>>>>>>> Stashed changes
        bool _winner = false;
};

#endif // DARTSPLAYER_H
