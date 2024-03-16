#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include <QJsonObject>
#include <QString>

class DartsPlayer {
public:
        DartsPlayer();

        DartsPlayer(const QString& name);

        DartsPlayer(const QString& name, const QString& url, const QString& nationality);

        DartsPlayer(const QJsonObject& jsonObj);
        QJsonObject jsonObject() const;
        QString name() const;
        bool winner() const;
        void setWinner(bool status);
        QString winnerImageUrl() const;

private:
        QString _name = "";
        QString _winnerImageUrl = "qrc:/pictures/Ressources/Pictures/dartsplate.png";
        QString _nationality = "";
        bool _winner = false;
};

#endif // DARTSPLAYER_H
