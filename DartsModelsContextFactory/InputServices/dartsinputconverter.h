#ifndef DARTSINPUTCONVERTER_H
#define DARTSINPUTCONVERTER_H
#include <quuid.h>
#include "InputServices/dartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DbSLAs/imodelconverter.h"
class DartsInputConverter : public IModelConverter<IModel<QUuid>>
{
public:
    Json create(Model *model) const override;
    Model *create(const Json &d) const override;
    Model *create(const ByteArray &byteArray) const override;
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QJsonArray toJsonArray(const QVector<IModel<QUuid>*> &models) const;
    QJsonObject toJsonObject(IModel<QUuid>* model) const;
    Model *toModel(const Json &json) const;
};
#endif // DARTSINPUTJSONASSEMBLER_H
