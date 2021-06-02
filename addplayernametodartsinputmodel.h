#ifndef ADDPLAYERNAMETODARTSINPUTMODEL_H
#define ADDPLAYERNAMETODARTSINPUTMODEL_H

#include "idartsscoreinput.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddPlayerNameToDartsInputModel :
        public IBinaryService<const IModel<QUuid,QByteArray>*,
                              const QString&,
                              const IModel<QUuid,QByteArray>*>
{
public:
    const IModel<QUuid,QByteArray>* service(const IModel<QUuid,QByteArray>* dartsScore,
                                                        const QString& playerName) override
    {
        auto inputModel = dynamic_cast<const IPlayerInput*>(dartsScore);
        auto mutableModel = const_cast<IPlayerInput*>(inputModel);
        mutableModel->setPlayerName(playerName);
        return mutableModel;
    }
};
#endif // ADDPLAYERNAMETODARTSINPUTMODEL_H
