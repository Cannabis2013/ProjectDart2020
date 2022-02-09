#ifndef BYTEARRAYTOINPUTS_H
#define BYTEARRAYTOINPUTS_H
#include "Routines/IJsonToModels.h"
template<typename T> class IJsonToSnapShot;
class SnapShot;
class ServicesContext;
class ByteArrayToInputs : public IJsonToModels<SnapShot>
{
public:
    typedef IJsonToSnapShot<SnapShot> JsonToSnapShot;
    ByteArrayToInputs(ServicesContext *provider);
    virtual Models convert(const ByteArray &ba) const override;
private:
    ServicesContext *_provider;
    JsonToSnapShot *_jsonToSnapShot;
};

#endif // BYTEARRAYTOINPUTS_H
