#ifndef GETTOURNAMENTASJSON_H
#define GETTOURNAMENTASJSON_H

#include <DartsModelsContext/Contracts/Routines/igettournamentasjson.h>

template<typename T> class IDbContext;
template<typename T> class IModelConverter;
class QJsonArray;

class GetTournamentAsJson : public IGetTournamentAsJson<IModel<QUuid>>
{
public:
    QByteArray tournamentToJson(const QUuid &ID, const DartsModelsServices *services) const override;
    QByteArray tournamentToJson(const QString &ID, const DartsModelsServices *services) const override;
    ByteArray tournamentToJson(const int &index, const DartsModelsServices *services) const override;
private:
    Model *getTournamentByID(const QUuid &ID, const DartsModelsServices *services) const;
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
