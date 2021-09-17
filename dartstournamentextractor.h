#ifndef DARTSTOURNAMENTEXTRACTOR_H
#define DARTSTOURNAMENTEXTRACTOR_H

#include "idartstournamentextractor.h"
class DartsTournamentExtractor : public IDartsTournamentExtractor
{
public:
    virtual QString title(const QJsonObject &obj) const override
    {
        return obj.value("title").toString();
    }
    virtual int gameMode(const QJsonObject &obj) const override
    {
        return obj.value("gameMode").toInt();
    }
    virtual int status(const QJsonObject &obj) const override
    {
        return obj.value("status").toInt();
    }
    virtual QUuid winnerId(const QJsonObject &obj) const override
    {
        return toId(obj.value("winnerId").toString());
    }
    virtual QString winnerName(const QJsonObject &obj) const override
    {
        return obj.value("winnerName").toString();
    }
    virtual int keyPoint(const QJsonObject &obj) const override
    {
        return obj.value("keyPoint").toInt();
    }
    virtual int displayHint(const QJsonObject &obj) const override
    {
        return obj.value("displayHint").toInt();
    }
    virtual int inputHint(const QJsonObject &obj) const override
    {
        return obj.value("inputHint").toInt();
    }
private:
    QUuid toId(const QString &string) const
    {
        return QUuid::fromString(string);
    }
};

#endif // DARTSTOURNAMENTEXTRACTOR_H
