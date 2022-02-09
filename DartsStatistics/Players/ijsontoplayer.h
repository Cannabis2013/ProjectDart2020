#ifndef IJSONTOPLAYER_H
#define IJSONTOPLAYER_H
class QJsonObject;
template<typename TModel>
class IJsonToPlayer
{
public:
    typedef QJsonObject Json;
    virtual TModel create(const Json &json) const = 0;
};

#endif // ICREATEPLAYER_H
