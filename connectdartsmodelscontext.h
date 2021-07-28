#ifndef CONNECTDARTSMODELSCONTEXT_H
#define CONNECTDARTSMODELSCONTEXT_H

#include "iconnectdartsmodelscontext.h"
#include "qobject.h"

class ConnectDartsModelsContext : public
        IConnectDartsModelsContext
{
public:
    void connect(AbstractApplicationInterface*application, AbstractDartsModelsContext*modelsService) override;
private:
    void registerTypes();
};

#endif // CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
