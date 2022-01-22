#ifndef SAVETOSTORAGE_H
#define SAVETOSTORAGE_H
#include "DbSLAs/abstractsavetostorage.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include "ModelSLAs/imodel.h"
#include "DbSLAs/idbcontext.h"
#include "DbSLAs/imodelconverter.h"
#include "FileIOSLAs/ifiledataio.h"
#include "DbSLAs/idbjsonbuilder.h"
class SaveToStorage : public AbstractSaveToStorage<IModel<QUuid>>
{
public:
    typedef QVector<BaseModel*> Models;
    virtual bool save(const QVector<BaseModel *> &models, JsonBuilder *builder, Converter *converter, IODevice *ioDevice) override;
    virtual bool save(const std::initializer_list<ServiceProvider> &list) override;
private:
    QJsonObject toJsonObject(const QByteArray &byteArray);
    QJsonArray toJsonArray(const Models &models, Converter *cvtr);
    QByteArray toData(const QJsonObject &obj);
};


#endif // SAVETOSTORAGE_H
