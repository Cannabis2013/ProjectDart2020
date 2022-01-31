#ifndef IJSONTOPLAYER_H
#define IJSONTOPLAYER_H
class QJsonObject;
namespace  Statistics{
    class IJsonToPlayer;
}
template<typename TModel>
class IJsonToPlayer
{
public:
    typedef TModel Player;
    typedef QJsonObject Json;
    virtual Player create(const Json &json) const = 0;
};

#endif // ICREATEPLAYER_H
