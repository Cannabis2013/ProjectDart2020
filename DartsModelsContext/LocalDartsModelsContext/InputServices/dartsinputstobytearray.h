#ifndef DARTSINPUTSTOBYTEARRAY_H
#define DARTSINPUTSTOBYTEARRAY_H

#include <DartsModelsContext/Contracts/Routines/idartsinputstojson.h>

class QJsonArray;
class DartsModelsServices;
class QUuid;
template<typename T> class IModel;

class IDartsInput;

class DartsInputsToByteArray : public IDartsInputsToJson<IModel<QUuid>>
{
public:
    typedef IModel<QUuid> Model;
    typedef QVector<Model*> Models;
    ByteArray fromInputs(const QUuid &tournamentID, const DartsModelsServices *services) const override;
private:
    Models getInputsFromMemory(const QUuid &tournamentID, const DartsModelsServices *services) const;
    QJsonArray toJsonArray(const Models &models, const DartsModelsServices *services) const;
};
#endif // DARTSINPUTSTOJSON_H
