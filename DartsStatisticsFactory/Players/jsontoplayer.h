#ifndef JSONTOPLAYER_H
#define JSONTOPLAYER_H
#include "Players/ijsontoplayer.h"
struct PlayerStat;
class JsonToPlayer : public IJsonToPlayer<PlayerStat>
{
public:
    virtual Player create(const Json &json) const override;
};
#endif // JSONTOPLAYER_H
