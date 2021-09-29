#ifndef CREATEPLAYERSFROMJSON_H
#define CREATEPLAYERSFROMJSON_H

#include "ModelsContext/MCJsonSLAs/icreatemodelsfromjson.h"
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "PlayerModelsContext/Services/playermodel.h"

class CreatePlayersFromJson : public ICreateModelsFromJson
{
public:
    virtual QVector<const IModel<QUuid>*> create(const QByteArray &json) const override;
private:
    QJsonArray createArray(const QByteArray &json) const;
};

#endif // PLAYERMODELJSONEXTRACTOR_H
