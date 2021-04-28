#ifndef PLAYERJSONASSEMBLER_H
#define PLAYERJSONASSEMBLER_H

#include "iplayerjsonassemblerservice.h"

#include <qvector.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "imodel.h"
#include "playermodel.h"

class PlayerJsonAssembler : public IPlayerJsonAssemblerService<QJsonArray,QVector<const IModel<QUuid>*>>
{
public:

    // IPlayerJsonAssemblerService interface
public:
    QJsonArray assembleJsonArrayFromModels(const QVector<const IModel<QUuid> *>& models);
};

#endif // PLAYERJSONASSEMBLER_H
