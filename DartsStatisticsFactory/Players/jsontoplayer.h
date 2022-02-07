#ifndef JSONTOPLAYER_H
#define JSONTOPLAYER_H
#include "Players/ijsontoplayer.h"
struct CurrentStats;
class JsonToPlayer : public IJsonToPlayer<CurrentStats>
{
public:
    virtual Player create(const Json &json) const override;
};
#endif // JSONTOPLAYER_H
