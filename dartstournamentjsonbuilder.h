#ifndef DARTSTOURNAMENTJSONBUILDER_H
#define DARTSTOURNAMENTJSONBUILDER_H

#include "idartstournamentjsonbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace ModelsContext {
    class DartsTournamentJsonBuilder : public IDartsTournamentJsonBuilder
    {
    public:
        virtual Json createJson(const QVector<const Tournament *> &tournaments) const override
        {
            QJsonArray arr;
            for (const auto &tournament : tournaments)
                arr << createJsonobject(tournament);
            return createJsonByteArray(arr);
        }
        virtual Json createJson(const Tournament *tournament) const override
        {
            return createJsonByteArray(createJsonobject(tournament));
        }
    private:
        QJsonObject createJsonobject(const Tournament *tournament) const
        {
            QJsonObject obj;
            auto dartsTournament = dynamic_cast<const IDartsTournament*>(tournament);
            obj["tournamentId"] = dartsTournament->id().toString(QUuid::WithoutBraces);
            obj["title"] = dartsTournament->title();
            obj["gameMode"] = dartsTournament->gameMode();
            obj["attempts"] = dartsTournament->attempts();
            obj["keyPoint"] = dartsTournament->keyPoint();
            obj["displayHint"] = dartsTournament->displayHint();
            obj["inputHint"] = dartsTournament->inputHint();
            obj["winnerId"] = dartsTournament->winnerId().toString(QUuid::WithoutBraces);
            obj["terminalKeyCode"] = dartsTournament->terminalKeyCode();
            obj["assignedPlayerIds"] = createArray(dartsTournament->assignedPlayerIds());
            obj["assignedPlayerNames"] = createArray(dartsTournament->assignedPlayerNames());
            return obj;
        }
        QByteArray createJsonByteArray(const QJsonObject &obj) const
        {
            auto document = QJsonDocument(obj);
            auto json = document.toJson();
            return json;
        }
        QByteArray createJsonByteArray(const QJsonArray &arr) const
        {
            auto document = QJsonDocument(arr);
            auto json = document.toJson();
            return json;
        }
        QJsonArray createArray(const QVector<QUuid> &assignedPlayerIds) const
        {
            QJsonArray arr;
            for (const auto& assignedPlayerId : assignedPlayerIds)
                arr << assignedPlayerId.toString(QUuid::WithoutBraces);
            return arr;
        }
        QJsonArray createArray(const QVector<QString> &strings) const
        {
            QJsonArray arr;
            for (const auto& string : strings)
                arr << string;
            return arr;
        }
    };
}


#endif // CREATEJSONFROMDARTSTOURNAMENTMODELS_H
