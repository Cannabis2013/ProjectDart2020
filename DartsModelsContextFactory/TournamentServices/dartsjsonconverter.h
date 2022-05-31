#ifndef DARTSJSONCONVERTER_H
#define DARTSJSONCONVERTER_H
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <quuid.h>
#include <TournamentModels/dartstournament.h>
#include "TournamentModelsSLAs/idartstournament.h"
#include "ModelSLAs/imodel.h"
#include "DbSLAs/imodelconverter.h"
class DartsJsonConverter : public IModelConverter<IModel<QUuid>>
{
public:
    virtual Json convert(Model *m) const override;
    virtual Model *convert(const ByteArray &byteArray) const override;
    virtual Model *convert(const Json &d) const override;
private:
    QJsonObject toJsonObject(IDartsTournament* model) const;
    void fromPlayerDetails(IModel<QUuid> *model, QJsonObject &obj) const;
    QJsonObject toJsonObject(const QUuid &id, const QString &name) const;
    IDartsTournament* fromJsonObject(const QJsonObject& obj) const;
    void setTournamentPlayerDetails(DartsTournament *tournament, const QJsonObject &obj) const;
    QUuid toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue = "") const;
};
#endif // DARTSJSONCONVERTER_H
