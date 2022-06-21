#ifndef IDCINPUTEVALUATOR_H
#define IDCINPUTEVALUATOR_H
#include <qobject.h>

struct DCIndex;
struct DCPlayer;
struct DCMeta;
struct DCInput;

class IDCInputEvaluator
{
public:
    virtual void evaluate(DCInput &input, DCMeta *meta, const DCPlayer &player) = 0;
};
#endif // IPOINTVALIDATOR_H
