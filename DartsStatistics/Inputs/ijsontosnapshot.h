#ifndef IJSONTOSNAPSHOT_H
#define IJSONTOSNAPSHOT_H
class QJsonObject;
template<typename TSnapShot>
class IJsonToSnapShot
{
public:
    typedef QJsonObject Json;
    virtual TSnapShot convert(const Json &json) const = 0;
};

#endif // ICONVERTINPUT_H
