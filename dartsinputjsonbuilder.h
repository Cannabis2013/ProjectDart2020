#ifndef DARTSINPUTJSONBUILDER_H
#define DARTSINPUTJSONBUILDER_H

#include <quuid.h>
#include "DartsModelsContext/DMCInputServices/dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsModelsContext/InputsDbSLAs/idartsinputjsonbuilder.h"

class DartsInputJsonBuilder : public IDartsInputJsonBuilder
{
public:
    virtual QByteArray dartsInputJson(IModel<QUuid> *model) const override;
    QByteArray dartsInputsJson(const QVector<IModel<QUuid>*> &models) const override;
private:
    QJsonArray createJsonArray(const QVector<IModel<QUuid>*> &models) const;
    QJsonObject toJsonObject(IModel<QUuid>* model) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
};
#endif // DARTSINPUTJSONASSEMBLER_H
