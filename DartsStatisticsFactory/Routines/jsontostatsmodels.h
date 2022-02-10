#ifndef JSONTOSTATSMODELS_H
#define JSONTOSTATSMODELS_H
#include <Routines/IJsonToModels.h>
template<typename T> class IJsonToStatsModel;
class ServicesContext;
class CurrentStat;
class JsonToStatsModels : public IJsonToModels<CurrentStat>
{
public:
    JsonToStatsModels(ServicesContext *provider);
    virtual Models convert(const ByteArray &ba) const override;
private:
    IJsonToStatsModel<CurrentStat> *_converter;
};

#endif // JSONTOSTATSMODELS_H
