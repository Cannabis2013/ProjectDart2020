#ifndef ASSEMBLEDPC_H
#define ASSEMBLEDPC_H

class AbstractDartsContext;
class DartsController;
class InjectDPCRoutines;
class DPCIndexServices;
class DPCInjectIptServices;
class DPCInjectPlaServices;
class DCInjectMetaClient;
class DCInjectFinClient;
class IDartsController;

class AssembleDPC
{
public:
        AssembleDPC();
        DartsController *assemble(AbstractDartsContext *modelsContext);
private:
        DCInjectFinClient *injectFinServices;
        DCInjectMetaClient *injectMetaServices;
        DPCInjectPlaServices *injectPlaServices;
        DPCInjectIptServices *injectIptServices;
        DPCIndexServices *injectIdxServices;
        InjectDPCRoutines *injectRoutines;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
