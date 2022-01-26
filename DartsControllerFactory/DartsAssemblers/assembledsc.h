#ifndef ASSEMBLEDSC_H
#define ASSEMBLEDSC_H
class DCInjectRoutineServices;
class DSCStatsInjector;
class DSCJsonResponseInjector;
class DSCInputInjector;
class DSCIndexInjector;
class DSCInjectPlaServives;
class IDartsCtrl;
class DCInjectFinClient;
class DCInjectMetaClient;
class AssembleDSC
{
public:
    AssembleDSC();
    IDartsCtrl *assemble();
private:
    DCInjectFinClient *finInjector;
    DCInjectMetaClient *metaInjector;
    DSCInjectPlaServives *plaCtxInjector;
    DSCIndexInjector *indexInjector;
    DSCInputInjector *inputInjector;
    DSCJsonResponseInjector *jsonInjector;
    DSCStatsInjector *statsInjector;
    DCInjectRoutineServices *loaderInjector;
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
