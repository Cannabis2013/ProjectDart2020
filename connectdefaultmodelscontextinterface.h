#ifndef CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
#define CONNECTDEFAULTMODELSCONTEXTINTERFACE_H

#include "iconnectmodelsinterface.h"
#include "qobject.h"

class ConnectDefaultModelsContextInterface : public
        IConnectModelsInterface
{
public:
    void connect(AbstractApplicationInterface*application, AbstractModelsService*modelsService) override;
private:
    void registerTypes();
};

#endif // CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
