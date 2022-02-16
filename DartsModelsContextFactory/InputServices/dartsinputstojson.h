#ifndef DARTSINPUTSTOJSON_H
#define DARTSINPUTSTOJSON_H
#include "InputModelsSLAs/idartsinputstojson.h"
template<typename T>
class IModelConverter;
template<typename T>
class IDbContext;
class DartsModelsServices;
class QUuid;
template<typename T>
class IModel;
class QJsonArray;
class QJsonObject;
class QByteArray;
class IDartsInput;
class DartsInputsToJson : public IDartsInputsToJson<IModel<QUuid>>
{
public:
    typedef IDbContext<Model> DbContext;
    typedef IModelConverter<Model> ModelConverter;
    DartsInputsToJson(DartsModelsServices *services);
    ByteArray fromInputs(const QUuid &tournamentID) const override;
private:
    QByteArray toByteArray(const QJsonArray &arr) const;
    DartsModelsServices *_services;
    DbContext *_iptsDb;
    ModelConverter *_cvtr;
};
#endif // DARTSINPUTSTOJSON_H
