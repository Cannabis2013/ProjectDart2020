#ifndef DARTSCONVERTTOJSON_H
#define DARTSCONVERTTOJSON_H
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
template<typename T> class IDbContext;
template<typename T> class IModelConverter;
class QJsonArray;
class DartsConvertToJson : public IDartsJsonBuilder<IModel<QUuid>>
{
public:
    QByteArray tournamentToJson(const QUuid &ID, const DartsModelsServices *services) const override;
    QByteArray tournamentToJson(const QString &ID, const DartsModelsServices *services) const override;
    ByteArray tournamentToJson(const int &index, const DartsModelsServices *services) const override;
    QByteArray tournamentsToJson(const DartsModelsServices *services) const override;
private:
    Model *getTournamentByID(const QUuid &ID, const DartsModelsServices *services) const;
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models, const DartsModelsServices *services) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
