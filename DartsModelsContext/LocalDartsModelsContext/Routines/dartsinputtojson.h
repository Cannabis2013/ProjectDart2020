#ifndef DARTSINPUTTOJSON_H
#define DARTSINPUTTOJSON_H

#include <DartsModelsContext/Contracts/Routines/idartsinputtojson.h>

class IDartsIndex;
template<typename T> class IModel;

class DartsInputToJson : public IDartsInputToJson<IModel<QUuid>>
{
public:
    typedef IModel<QUuid> Model;
    virtual ByteArray toJson(const QUuid &tournamentID, const QString &name,
                             const ByteArray &idxindexAsByteArray, const DartsModelsServices *services) const override;
private:
    Model *getInputModel(IDartsIndex *index, const QUuid &tournamentID, const QString &name,
                        const DartsModelsServices *services) const;
    QByteArray toByteArray(Model *model, const DartsModelsServices *services) const;
};
#endif // DARTSINPUTTOJSON_H
