#ifndef IJSONTOINPUT_H
#define IJSONTOINPUT_H
class QJsonObject;
template<typename TInput>
class IJsonToInput
{
public:
    typedef TInput Input;
    typedef QJsonObject Json;
    virtual Input convert(const Json &json) const = 0;
};

#endif // ICONVERTINPUT_H
