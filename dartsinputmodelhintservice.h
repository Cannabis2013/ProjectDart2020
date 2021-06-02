#ifndef DARTSPOINTMODELHINTSERVICE_H
#define DARTSPOINTMODELHINTSERVICE_H

#include "ibinaryservice.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsInputModelHintService :
            public IBinaryService<const IModel<QUuid,QByteArray>*,const int&, const IModel<QUuid,QByteArray>*>
    {
    public:
        const IModel<QUuid,QByteArray>* service(const IModel<QUuid,QByteArray>* model, const int& hint) override
        {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            auto mutableModel = const_cast<IPlayerInput*>(inputModel);
            mutableModel->setHint(hint);
            return mutableModel;
        }
    };
}


#endif // DARTSPOINTMODELHINTSERVICE_H
