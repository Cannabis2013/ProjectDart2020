#ifndef ASSEMBLEDSC_H
#define ASSEMBLEDSC_H
class AbstractDartsContext;
class DartsController;
class InjectDSCRoutines;
class DSCInputInjector;
class DSCIndexInjector;
class DSCInjectPlaServives;
class IDartsController;
class DCInjectFinClient;
class DCInjectMetaClient;
class AssembleDSC
{
public:
    AssembleDSC();
    DartsController *assemble(AbstractDartsContext *modelsContext);
private:
    DCInjectFinClient *finInjector;
    DCInjectMetaClient *metaInjector;
    DSCInjectPlaServives *plaCtxInjector;
    DSCIndexInjector *indexInjector;
    DSCInputInjector *inputInjector;
    InjectDSCRoutines *injectRoutines;
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
