#ifndef DARTSINPUTJSONBUILDER_H
#define DARTSINPUTJSONBUILDER_H

#include <quuid.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsModelsContext/InputsDbSLAs/idartsinputjsonbuilder.h"

class DartsInputJsonBuilder : public IDartsInputJsonBuilder
{
public:
    virtual QByteArray json(IModel<QUuid> *model, const DartsMetaModel &meta) const override;
    QByteArray json(const QVector<IModel<QUuid>*> &models) const override;
private:
    QJsonArray toJsonArray(const QVector<IModel<QUuid>*> &models) const;
    QJsonObject toJsonObject(IModel<QUuid>* model) const;
    QJsonObject toDefaultJsonObject(const DartsMetaModel &meta) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QString toString(const QUuid &id) const;
};
#endif // DARTSINPUTJSONASSEMBLER_H
