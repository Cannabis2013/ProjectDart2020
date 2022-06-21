#ifndef DARTSINPUTCONVERTER_H
#define DARTSINPUTCONVERTER_H

#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <DartsModelsContext/Contracts/Db/imodelconverter.h>

template<typename  T>class IModel;

class DartsInputConverter : public IModelConverter<IModel<QUuid>>
{
public:
    Json convert(Model *model) const override;
    Model *convert(const Json &d) const override;
    Model *convert(const ByteArray &byteArray) const override;
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QJsonArray toJsonArray(const QVector<IModel<QUuid>*> &models) const;
    QJsonObject toJsonObject(IModel<QUuid>* model) const;
    Model *toModel(const Json &json) const;
};
#endif // DARTSINPUTJSONASSEMBLER_H
