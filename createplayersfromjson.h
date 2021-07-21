#ifndef CREATEPLAYERSFROMJSON_H
#define CREATEPLAYERSFROMJSON_H

#include "icreateplayersfromjson.h"
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "playermodel.h"
class CreatePlayersFromJson : public ICreatePlayersFromJson
{
public:
    virtual QVector<const IModel<QUuid>*> create(const QByteArray &json) const override;
private:
    QJsonArray createArray(const QByteArray &json) const;
};

#endif // PLAYERMODELJSONEXTRACTOR_H
