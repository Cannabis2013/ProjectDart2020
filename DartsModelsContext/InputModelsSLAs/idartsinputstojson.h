#ifndef IDARTSINPUTSTOJSON_H
#define IDARTSINPUTSTOJSON_H
class QUuid;
class QJsonObject;
class QByteArray;
template<typename T>
class QVector;
template<typename TModel>
class IDartsInputsToJson
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef QByteArray ByteArray;
    virtual ByteArray fromInputs(const QUuid &tournamentID) const = 0;
};
#endif // IINPUTSTOJSON_H
