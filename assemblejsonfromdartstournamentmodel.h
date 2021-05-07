#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENTMODEL_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENTMODEL_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "idartstournament.h"
#include <quuid.h>

class AssembleJsonFromDartsTournament :
        public IUnaryService<const IDartsTournament<QUuid,QString>*,QByteArray>
{
public:
    QByteArray service(const IDartsTournament<QUuid,QString>* model) override
    {
        QJsonObject obj;
        obj["tournamentId"] = model->id().toString(QUuid::WithoutBraces);
        obj["gameMode"] = model->gameMode();
        obj["attempts"] = model->attempts();
        obj["keyPoint"] = model->keyPoint();
        obj["terminalKeyCode"] = model->terminalKeyCode();
        obj["inputHint"] = model->inputHint();
        obj["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        auto json = QJsonDocument(obj).toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODEL_H
