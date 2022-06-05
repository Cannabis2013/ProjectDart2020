#ifndef DARTSMETAMODELBUILDER_H
#define DARTSMETAMODELBUILDER_H

#include <DartsModelsContext/TournamentsSLAs/idartscreatemeta.h>

class QJsonValue;
class QJsonObject;

class DartsMetaModelBuilder : public IDartsCreateMeta
{
public:
    virtual DartsMetaModel create(const QByteArray &json) const override;
    virtual DartsMetaModel create(const QUuid &tournament, const QUuid &player) const override;
private:
    QJsonObject toJsonObject(const QByteArray &json) const;
    DartsMetaModel toModel(const QJsonObject &obj) const;
    QUuid toId(const QJsonValue &value) const;
};
#endif // DARTSMETAMODELBUILDER_H
