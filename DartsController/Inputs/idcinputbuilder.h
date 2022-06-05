#ifndef IDCINPUTBUILDER_H
#define IDCINPUTBUILDER_H


class QJsonObject;
class QString;
class QByteArray;

template<typename TModel>
class IDCInputBuilder
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    virtual Model create(const QString &name, const int &remainingScore) const = 0;
    virtual Model create() const = 0;
};
#endif // IDCIPTCONVERTER_H
