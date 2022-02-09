#ifndef JSONTOSNAPSHOT_H
#define JSONTOSNAPSHOT_H
#include "Inputs/ijsontosnapshot.h"
struct SnapShot;
class JsonToSnapShot : public IJsonToSnapShot<SnapShot>
{
public:
    virtual SnapShot convert(const Json &json) const override;
};

#endif // JSONTOINPUT_H
