#ifndef ASSEMBLEDPC_H
#define ASSEMBLEDPC_H
class InjectDPCRoutines;
class DPCInjectStatsServices;
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
    DPCInjectStatsServices *injectStatsServices;
    InjectDPCRoutines *injectRoutines;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
