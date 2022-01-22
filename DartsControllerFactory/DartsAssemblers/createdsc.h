#ifndef CREATEDSC_H
#define CREATEDSC_H
class DSCStatsInjector;
class DSCJsonResponseInjector;
class DSCInputInjector;
class DSCIndexInjector;
class DSCInjectPlaServives;
class AbsDartsCtrl;
class DCInjectFinClient;
class DCInjectMetaClient;
class CreateDSC
{
public:
    CreateDSC();
    AbsDartsCtrl *create();
private:
    DCInjectFinClient *finInjector;
    DCInjectMetaClient *metaInjector;
    DSCInjectPlaServives *plaCtxInjector;
    DSCIndexInjector *indexInjector;
    DSCInputInjector *inputInjector;
    DSCJsonResponseInjector *jsonInjector;
    DSCStatsInjector *statsInjector;
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
