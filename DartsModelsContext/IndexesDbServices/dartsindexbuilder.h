#ifndef DARTSINDEXBUILDER_H
#define DARTSINDEXBUILDER_H
#include <QJsonArray>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DartsModelsContext/IndexesDbSLAs/icreatedartsinexesmodels.h"
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DartsIndexBuilder : public IDartsIndexesBuilder
{
public:
    virtual IDartsIndex *index(const QUuid &tournamentId) const override
    {
        auto model = new DartsIndex;
        model->setId(QUuid::createUuid());
        model->setTournamentId(tournamentId);
        model->setRoundIndex(1);
        return model;
    }
    virtual IDartsIndex *index(const QByteArray &json) const override
    {
        return toInputIndexModel(toJsonObject(json));
    }
    virtual QVector<IModel<QUuid> *> indexes(const QByteArray &json) const override
    {
        return toModels(toJsonArray(json));
    }
    virtual IDartsIndex *reqIndex(const QByteArray &json) const override
    {
        return toReqIndexModel(toJsonObject(json));
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
            models << toInputIndexModel((*i).toObject());
        return models;
    }
    DartsIndex *toInputIndexModel(const QJsonObject &obj) const
    {
        auto model = new DartsIndex;
        model->setId(QUuid::fromString(obj.value("id").toString()));
        model->setTournamentId(QUuid::fromString(obj.value("tournamentId").toString()));
        model->setTotalTurns(obj.value("totalTurns").toInt());
        model->setTurnIndex(obj.value("turnIndex").toInt());
        model->setRoundIndex(obj.value("roundIndex").toInt());
        model->setSetIndex(obj.value("setIndex").toInt());
        model->setAttemptIndex(obj.value("attemptIndex").toInt());
        return model;
    }
    DartsIndex *toReqIndexModel(const QJsonObject &obj) const
    {
        auto model = new DartsIndex;
        model->setId(QUuid::fromString(obj.value("id").toString()));
        model->setTournamentId(QUuid::fromString(obj.value("tournamentId").toString()));
        model->setTotalTurns(obj.value("reqTotalTurns").toInt());
        model->setTurnIndex(obj.value("reqTurnIndex").toInt());
        model->setRoundIndex(obj.value("reqRoundIndex").toInt());
        model->setSetIndex(obj.value("reqSetIndex").toInt());
        model->setAttemptIndex(obj.value("reqAttemptIndex").toInt());
        return model;
    }
};

#endif // DARTSINDEXESBUILDER_H
