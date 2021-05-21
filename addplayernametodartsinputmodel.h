#ifndef ADDPLAYERNAMETODARTSINPUTMODEL_H
#define ADDPLAYERNAMETODARTSINPUTMODEL_H

#include "idartsscoreinput.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddPlayerNameToDartsInputModel :
        public IBinaryService<const DartsModelsContext::IPlayerInput*,
                              const QString&,
                              const DartsModelsContext::IPlayerInput*>
{
public:
    const DartsModelsContext::IPlayerInput* service(const DartsModelsContext::IPlayerInput* dartsScore,
                                                        const QString& playerName) override
    {
        auto mutableModel = const_cast<DartsModelsContext::IPlayerInput*>(dartsScore);
        mutableModel->setPlayerName(playerName);
        return mutableModel;
    }
};
#endif // ADDPLAYERNAMETODARTSINPUTMODEL_H
