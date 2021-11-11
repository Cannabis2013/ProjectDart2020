#ifndef DARTSINDEXBUILDER_H
#define DARTSINDEXBUILDER_H
#include <QJsonArray>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <DartsModelsContext/IndexesSLAs/idartsindexbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"

class DartsIndexBuilder : public IDartsIndexBuilder
{
public:
    IDartsIndex *index() const override
    {
        auto model = new DartsIndex;
        model->setRoundIndex(1);
        return model;
    }
    IDartsIndex *index(const QByteArray &json) const override
    {
        return toInputIndexModel(toJsonObject(json));
    }
    QVector<IDartsIndex *> indexes(const QByteArray &json) const override
    {
        return toModels(toJsonArray(json));
    }
    IDartsIndex *reqIndex(const QByteArray &json) const override
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
    QVector<IDartsIndex*> toModels(const QJsonArray &arr) const
    {
        QVector<IDartsIndex*> models;
        for (auto i = arr.begin(); i != arr.end(); ++i)
            models << toInputIndexModel((*i).toObject());
        return models;
    }
    DartsIndex *toInputIndexModel(const QJsonObject &obj) const
    {
        auto model = new DartsIndex;
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
        model->setTotalTurns(obj.value("reqTotalTurns").toInt());
        model->setTurnIndex(obj.value("reqTurnIndex").toInt());
        model->setRoundIndex(obj.value("reqRoundIndex").toInt());
        model->setSetIndex(obj.value("reqSetIndex").toInt());
        model->setAttemptIndex(obj.value("reqAttemptIndex").toInt());
        return model;
    }
};

#endif // DARTSINDEXESBUILDER_H
