#ifndef CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
#define CONNECTDEFAULTMODELSCONTEXTINTERFACE_H

#include "ibinaryservice.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"
#include "qobject.h"

class ConnectDefaultModelsContextInterface :
        public IBinaryService<AbstractApplicationInterface*,
        AbstractModelsService*,
        void>
{
public:
    void service(AbstractApplicationInterface*application, AbstractModelsService*modelsService) override;
private:
    void registerTypes();
};

#endif // CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
