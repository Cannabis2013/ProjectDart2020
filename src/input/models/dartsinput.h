#ifndef DARTSINTERNALINPUT_H
#define DARTSINTERNALINPUT_H

#include <QString>

class QJsonObject;

class DartsInput
{
public:
    DartsInput(const QJsonObject &jsonObj);
    DartsInput(const QString &mod, const int &point);
    DartsInput();

    QJsonObject toJsonObject() const;

    int point() const;
    void setPoint(int point);
    QString mod() const;
    QString playerName() const;

    int roundIndex() const;
    int turnId() const;
    void setTurnId(int newTurnId);
    void setRoundIndex(int newRoundIndex);
    void setPlayerName(const QString &newPlayerName);

private:
    int _point = 0;
    QString _mod = "S";
    QString _playerName;
    int _turnId;
    int _roundIndex;
};
#endif // DARTSINTERNALINPUT_H
