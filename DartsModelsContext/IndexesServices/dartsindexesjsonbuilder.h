#ifndef DARTSINDEXESJSONBUILDER_H
#define DARTSINDEXESJSONBUILDER_H

#include "DartsModelsContext/IndexesDbSLAs/idartsindexes.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindexesjsonbuilder.h"
#include <QJsonArray>
#include <QJsonObject>
#include <qjsondocument.h>

class DartsIndexesJsonBuilder : public IDartsIndexesJsonBuilder
{
public:
    virtual QByteArray indexesModelJson(IModel<QUuid> *&model) const override
    {
        return toByteArray(toJsonObject(model));
    }
    virtual QByteArray indexesModelsJson(const QVector<IModel<QUuid> *> &models) const override
    {
        return toByteArray(toJsonArray(models));
    }
private:
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models) const
    {
        QJsonArray arr;
        for (const auto &model : models)
            arr << toJsonObject(model);
        return arr;
    }
    QJsonObject toJsonObject(IModel<QUuid> *model) const
    {
        auto indexesModel = dynamic_cast<IDartsIndexes*>(model);
        QJsonObject obj;
        obj["tournamentId"] = indexesModel->tournamentId().toString(QUuid::WithoutBraces);
        obj["totalTurns"] = indexesModel->totalTurns();
        obj["turnIndex"] = indexesModel->turnIndex();
        obj["roundIndex"] = indexesModel->roundIndex();
        obj["setIndex"] = indexesModel->setIndex();
        obj["attemptIndex"] = indexesModel->attemptIndex();
        return obj;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        return QJsonDocument(obj).toJson();
    }
    QByteArray toByteArray(const QJsonArray &arr) const
    {
        return QJsonDocument(arr).toJson();
    }
};

#endif // DARTSINDEXESJSONBUILDER_H
