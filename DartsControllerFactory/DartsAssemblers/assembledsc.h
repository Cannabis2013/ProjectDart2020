#ifndef ASSEMBLEDSC_H
#define ASSEMBLEDSC_H
class AbsDartsCtx;
class DartsController;
class InjectDSCRoutines;
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
    DartsController *assemble(AbsDartsCtx *modelsContext);
private:
    DCInjectFinClient *finInjector;
    DCInjectMetaClient *metaInjector;
    DSCInjectPlaServives *plaCtxInjector;
    DSCIndexInjector *indexInjector;
    DSCInputInjector *inputInjector;
    DSCJsonResponseInjector *jsonInjector;
    InjectDSCRoutines *injectRoutines;
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
