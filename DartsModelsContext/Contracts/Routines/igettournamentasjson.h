#ifndef IGETTOURNAMENTASJSON_H
#define IGETTOURNAMENTASJSON_H

class DartsModelsServices;
class QString;
class QByteArray;
class QJsonObject;
template<typename T>
class QVector;
class QUuid;
template<typename T>
class IModel;
template<typename TModel>
class IGetTournamentAsJson
{
public:
    typedef TModel Model;
    typedef QJsonObject JsonObject;
    typedef QByteArray ByteArray;
    virtual ByteArray tournamentToJson(const QUuid &tournamentId, const DartsModelsServices *services) const = 0;
    virtual ByteArray tournamentToJson(const QString &tournamentId, const DartsModelsServices *services) const = 0;
    virtual ByteArray tournamentToJson(const int &index, const DartsModelsServices *services) const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H