#ifndef CONNECTDARTSMODELSCONTEXT_H
#define CONNECTDARTSMODELSCONTEXT_H

#include "iconnectdartsmodelscontext.h"
#include "qobject.h"

class ConnectDartsModelsContext : public
        IConnectDartsModelsContext
{
public:
    void connect(AbstractApplicationInterface*application,
                 AbstractDartsModelsContext*modelsService,
                 AbstractDCBuilder *dcBuilder) override;
private:
    void connectDeleteTournamentInterface(AbstractApplicationInterface*application,
                                          AbstractDartsModelsContext*modelsService);
    void connectToDCBuilder(AbstractDartsModelsContext*modelsService, AbstractDCBuilder *dcBuilder);
    void registerTypes();
};

#endif // CONNECTDEFAULTMODELSCONTEXTINTERFACE_H
