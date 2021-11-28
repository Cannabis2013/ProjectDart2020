#ifndef DARTSINPUTSTOJSON_H
#define DARTSINPUTSTOJSON_H
#include <quuid.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ModelsContext/DbSLAs/icreatedatafrom.h"
class DartsInputsToJson : public ICreateDataFrom<IModel<QUuid>,QByteArray>
{
public:
    QByteArray create(const QVector<FromData*> &models, QByteArray &json) const override;
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QJsonArray toJsonArray(const QVector<IModel<QUuid>*> &models) const;
    QJsonObject toJsonObject(IModel<QUuid>* model) const;
};
#endif // DARTSINPUTJSONASSEMBLER_H
