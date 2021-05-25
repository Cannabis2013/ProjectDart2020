#ifndef ADDPLAYERNAMETODARTSINPUTMODEL_H
#define ADDPLAYERNAMETODARTSINPUTMODEL_H

#include "idartsscoreinput.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddPlayerNameToDartsInputModel :
        public IBinaryService<const DartsModelsContext::IDartsInput*,
                              const QString&,
                              const DartsModelsContext::IDartsInput*>
{
public:
    const DartsModelsContext::IDartsInput* service(const DartsModelsContext::IDartsInput* dartsScore,
                                                        const QString& playerName) override
    {
        auto mutableModel = const_cast<DartsModelsContext::IDartsInput*>(dartsScore);
        mutableModel->setPlayerName(playerName);
        return mutableModel;
    }
};
#endif // ADDPLAYERNAMETODARTSINPUTMODEL_H
