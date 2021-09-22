#ifndef CREATEJSONFROMTOURNAMENTDETAILS_H
#define CREATEJSONFROMTOURNAMENTDETAILS_H

#include "DartsTournamentJsonServices/icreatejsonfromtournamentdetails.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "abstractdartstournament.h"

class CreateJsonFromTournamentDetails : public ICreateJsonFromTournamentDetails
{
public:
    virtual QByteArray createFromAssignedPlayerDetails(const IModel<QUuid> *model) const override
    {
        auto tournament = dynamic_cast<const ITournament*>(model);
        auto arr = createJsonFromList(tournament->assignedPlayerIds(),tournament->assignedPlayerNames());
        return createByteArray(arr);
    }
    virtual QByteArray createFromWinnerDetails(const IModel<QUuid> *model) const override
    {
        auto tournament = dynamic_cast<const ITournament*>(model);
        QJsonObject obj;
        obj["winnerId"] = tournament->winnerId().toString(QUuid::WithoutBraces);
        obj["winnerName"] = tournament->winnerName();
        return createByteArray(obj);
    }
private:
    QJsonArray createJsonFromList(const QVector<QUuid> &playerIds,
                                  const QVector<QString> &playerNames) const
    {
        if(playerIds.count() != playerNames.count())
            throw "";
        QJsonArray arr;
        for (int i = 0;i < playerIds.count();i++)
        {
            auto playerId = playerIds.at(i);
            auto playerName = playerNames.at(i);
            arr << createObject(playerId,playerName);
        }
        return arr;
    }
    QJsonObject createObject(const QUuid &id, const QString &name) const
    {
        QJsonObject obj;
        obj["playerId"] = id.toString(QUuid::WithoutBraces);
        obj["playerName"] = name;
        return obj;
    }
    QJsonArray createJsonFromList(const QVector<QString> &playerNames) const
    {
        QJsonArray arr;
        for (const auto &playerName : playerNames)
            arr << playerName;
        return arr;
    }
    QByteArray createByteArray(const QJsonArray &arr) const
    {
        auto document = QJsonDocument(arr);
        auto byteArray = document.toJson();
        return byteArray;
    }
    QByteArray createByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        auto byteArray = document.toJson();
        return byteArray;
    }
};
#endif // CREATEJSONFROMTOURNAMENTDETAILS_H
