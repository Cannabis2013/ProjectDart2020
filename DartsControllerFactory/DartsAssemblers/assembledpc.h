#ifndef ASSEMBLEDPC_H
#define ASSEMBLEDPC_H
class InjectDPCRoutines;
class DPCInjectIdxServices;
class DPCInjectIptServices;
class DPCInjectPlaServices;
class DCInjectMetaClient;
class DCInjectFinClient;
class IDartsCtrl;
class AssembleDPC
{
public:
    AssembleDPC();
    IDartsCtrl *assemble();
private:
    DCInjectFinClient *injectFinServices;
    DCInjectMetaClient *injectMetaServices;
    DPCInjectPlaServices *injectPlaServices;
    DPCInjectIptServices *injectIptServices;
    DPCInjectIdxServices *injectIdxServices;
    InjectDPCRoutines *injectRoutines;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
