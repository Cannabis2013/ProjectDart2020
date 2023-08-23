#ifndef IDARTSINPUTSTOJSON_H
#define IDARTSINPUTSTOJSON_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <quuid.h>

template<typename TModel>
class IDartsInputsToJson
{
public:
    typedef TModel Model;
    typedef QVector<Model *> Models;
    typedef QByteArray ByteArray;
    virtual ByteArray fromInputs(const QUuid &tournamentID, const DartsModelsServices *services) const = 0;
};
#endif // IINPUTSTOJSON_H
