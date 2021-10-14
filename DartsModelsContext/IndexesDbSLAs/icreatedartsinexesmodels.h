#ifndef ICREATEDARTSINEXESMODELS_H
#define ICREATEDARTSINEXESMODELS_H

#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class IDartsIndexesBuilder
{
public:
    virtual IModel<QUuid> *indexesModel(const QUuid &tournamentId) const = 0;
    virtual IModel<QUuid> *indexesModel(const QByteArray &json) const = 0;
    virtual QVector<IModel<QUuid>*> indexesModels(const QByteArray &json) const = 0;
};

#include <QJsonArray>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DartsModelsContext/IndexesDbServices/dartsindexes.h"

class DartsIndexesBuilder : public IDartsIndexesBuilder
{
public:
    virtual IModel<QUuid> *indexesModel(const QUuid &tournamentId) const override
    {
        auto model = new DartsIndexes;
        model->setTournamentId(tournamentId);
        model->setRoundIndex(1);
        return model;
    }
    virtual IModel<QUuid> *indexesModel(const QByteArray &json) const override
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
        model->setTournamentId(QUuid::fromString(obj.value("tournamentId").toString()));
        model->setTotalTurns(obj.value("totalTurns").toInt());
        model->setTurnIndex(obj.value("turnIndex").toInt());
        model->setRoundIndex(obj.value("roundIndex").toInt());
        model->setSetIndex(obj.value("setIndex").toInt());
        model->setAttemptIndex(obj.value("attemptIndex").toInt());
        return model;
    }
};

#endif // ICREATEDARTSINEXESMODELS_H
