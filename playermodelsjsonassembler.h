#ifndef PLAYERJSONASSEMBLER_H
#define PLAYERJSONASSEMBLER_H

#include "iplayerjsonassemblerservice.h"

#include <qvector.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <quuid.h>
#include "imodel.h"
#include "playermodel.h"
#include "iunaryservice.h"

class PlayerModelsJsonAssembler : public IUnaryService<const QVector<const IPlayerModel<QUuid,QString>*>&,QJsonArray>
{
public:
    static PlayerModelsJsonAssembler* createInstance();
    QJsonArray service(const QVector<const IPlayerModel<QUuid, QString> *> &models) override;
};

#endif // PLAYERJSONASSEMBLER_H
