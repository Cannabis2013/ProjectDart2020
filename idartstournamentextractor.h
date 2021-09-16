#ifndef IDARTSTOURNAMENTEXTRACTOR_H
#define IDARTSTOURNAMENTEXTRACTOR_H

#include <qjsonobject.h>
class IDartsTournamentExtractor
{
public:
    virtual QString title(const QJsonObject &obj) const = 0;
    virtual int gameMode(const QJsonObject &obj) const = 0;
    virtual int status(const QJsonObject &obj) const = 0;
    virtual QUuid winnerId(const QJsonObject &obj) const = 0;
    virtual QString winnerName(const QJsonObject &obj) const = 0;
    virtual int attempts(const QJsonObject &obj) const = 0;
    virtual int keyPoint(const QJsonObject &obj) const = 0;
    virtual int terminalKeyCode(const QJsonObject &obj) const = 0;
    virtual int displayHint(const QJsonObject &obj) const = 0;
    virtual int inputHint(const QJsonObject &obj) const = 0;
};
#endif // DARTSTOURNAMENTEXTRACTOR_H
