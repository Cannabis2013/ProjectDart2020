#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
        DartsPlayer(const QString& name)
            : _name(name)
        {
        }

        DartsPlayer(const QJsonObject& jsonObj)
        {
                _name = jsonObj.value("name").toString("");
                _winner = jsonObj.value("winner").toBool();
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

        QJsonObject toJsonObject() const
        {
                QJsonObject jsonObj;
                jsonObj["name"] = _name;
                jsonObj["winner"] = _winner;
                return jsonObj;
        }

private:
        QString _name;
        bool _winner = false;
};

#endif // DARTSPLAYER_H
