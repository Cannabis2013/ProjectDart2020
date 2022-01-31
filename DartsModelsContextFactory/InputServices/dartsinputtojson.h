#ifndef DARTSINPUTTOJSON_H
#define DARTSINPUTTOJSON_H
#include <InputSLAs/idartsinputtojson.h>
template<typename T> class IModelConverter;
template<typename T> class IDartsIdxBuilder;
class IDartsIndex;
template<typename T> class IDbContext;
class DartsInputServices;
class DMCServices;
template<typename T> class IModel;
class QUuid;
class DartsInputToJson : public IDartsInputToJson<IModel<QUuid>>
{
public:
    typedef IDbContext<Model> DbContext;
    typedef IDartsIdxBuilder<IDartsIndex> IndexBuilder;
    typedef IModelConverter<Model> ModelConverter;
    DartsInputToJson(DMCServices *services);
    ByteArray toJson(const QUuid &tournamentID, const QString &name, const ByteArray &idxBa) const override;
private:
    DMCServices *_services;
    DartsInputServices *_iptServices;
    DbContext *_iptsDb;
    IndexBuilder *_idxBuilder;
    ModelConverter *_cvtr;
};
#endif // DARTSINPUTTOJSON_H
