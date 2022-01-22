#ifndef DARTSJSONBUILDER_H
#define DARTSJSONBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DbSLAs/imodelconverter.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
class DartsJsonBuilder : public IDartsJsonBuilder<IModel<QUuid>>
{
public:
    virtual QByteArray create(Model *model, ModelConverter *cvt) const override
    {
        return toByteArray(cvt->create(model));
    }
    virtual QByteArray create(const QVector<Model*> &models, ModelConverter *cvt) const override
    {
        return toByteArray(toJsonArray(models,cvt));
    }
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const
    {
        return QJsonDocument::fromJson(byteArray).object();
    }
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models, ModelConverter *cvt) const
    {
        QJsonArray arr;
        for (auto& model : models)
            arr << cvt->create(model);
        return arr;
    }
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
    QByteArray toByteArray(const QJsonArray &arr) const
    {
        auto document = QJsonDocument(arr);
        auto json = document.toJson();
        return json;
    }
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
