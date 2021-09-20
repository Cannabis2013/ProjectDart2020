#ifndef IDARTSPLAYERJSONBUILDER_H
#define IDARTSPLAYERJSONBUILDER_H

#include <qbytearray.h>
#include <quuid.h>
#include "ModelsContext/imodel.h"

class ICreateJsonFromPlayers
{
    // IPlayerJsonBuilder interface
public:
    virtual QByteArray createJson(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const = 0;
    virtual QByteArray createJson(const IModel<QUuid> *playerModel) const = 0;
    virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &playerModels) const = 0;
};
#endif // ICREATEJSONFROMDARTSPLAYERCREDENTIALS_H
