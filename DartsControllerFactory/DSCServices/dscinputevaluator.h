#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DCInputSLAs/idcinputevaluator.h"
class DCServices;
struct DCIndex;
template<typename T,typename U> class IDCPlayerManager;
template<typename T,typename U> class IDCIndexController;
template<typename T> class IDCMetaManager;
class DSCInputEvaluator : public IDCInputEvaluator
{
public:
    typedef IDCMetaManager<DCMeta> MetaManager;
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    DSCInputEvaluator(DCServices *services);
    void evaluate(DCInput &input) override;
private:
    int calcScore(const int &scoreCand, const int &remScore);
    void update(const int &scoreCand, DCInput &input, DCMeta *meta);
    const int minimumAllowedScore = 2;
    MetaManager *_metaManager;
    PlayerManager *_playerManager;
    IndexController *_indexController;
};
#endif // SCOREVALIDATOR_H
