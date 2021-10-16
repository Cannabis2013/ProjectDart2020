#ifndef DARTSINDEXESBUILDER_H
#define DARTSINDEXESBUILDER_H

#include <QJsonArray>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DartsModelsContext/IndexesDbSLAs/icreatedartsinexesmodels.h"
#include "DartsModelsContext/IndexesDbServices/dartsindexes.h"

class DartsIndexesBuilder : public IDartsIndexesBuilder
{
public:
    virtual IDartsIndexes *buildIndexes(const QUuid &tournamentId) const override
    {
        auto model = new DartsIndexes;
        model->setId(QUuid::createUuid());
        model->setTournamentId(tournamentId);
        model->setRoundIndex(1);
        return model;
    }
    virtual IDartsIndexes *buildIndexes(const QByteArray &json) const override
    {
        return toModel(toJsonObject(json));
    }
    virtual QVector<IModel<QUuid> *> indexesModels(const QByteArray &json) const override
    {
        return toModels(toJsonArray(json));
    }
private:
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        return QJsonDocument::fromJson(json).object();
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        return QJsonDocument::fromJson(json).array();
    }
    QVector<IModel<QUuid>*> toModels(const QJsonArray &arr) const
    {
        QVector<IModel<QUuid>*> models;
        for (auto i = arr.begin(); i != arr.end(); ++i)
            models << toModel((*i).toObject());
        return models;
    }
    DartsIndexes *toModel(const QJsonObject &obj) const
    {
        auto model = new DartsIndexes;
        model->setId(QUuid::fromString(obj.value("id").toString()));
        model->setTournamentId(QUuid::fromString(obj.value("tournamentId").toString()));
        model->setTotalTurns(obj.value("totalTurns").toInt());
        model->setTurnIndex(obj.value("turnIndex").toInt());
        model->setRoundIndex(obj.value("roundIndex").toInt());
        model->setSetIndex(obj.value("setIndex").toInt());
        model->setAttemptIndex(obj.value("attemptIndex").toInt());
        return model;
    }
};

#endif // DARTSINDEXESBUILDER_H
