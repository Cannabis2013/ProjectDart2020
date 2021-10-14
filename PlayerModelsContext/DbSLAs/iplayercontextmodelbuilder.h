#ifndef IPLAYERCONTEXTMODELBUILDER_H
#define IPLAYERCONTEXTMODELBUILDER_H

#include "ModelsContext/MCModelsSLAs/imodel.h"
#include <QByteArray>
#include <quuid.h>

class IPlayerContextModelBuilder
{
public:
    virtual IModel<QUuid>* createPlayer(const QByteArray &json) const = 0;
    virtual QVector<IModel<QUuid>*> createPlayers(const QByteArray &json) const = 0;
};

#endif // IPLAYERCONTEXTMODELBUILDER_H
