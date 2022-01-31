#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H
class QString;
class QByteArray;
class QJsonObject;
template<typename T>
class QVector;
class QUuid;
template<typename T>
class IModel;
template<typename TModel>
class IDartsJsonBuilder
{
public:
    typedef TModel Model;
    typedef QJsonObject JsonObject;
    typedef QByteArray ByteArray;
    virtual ByteArray fromTournament(const QUuid &tournamentId) const = 0;
    virtual ByteArray fromTournament(const QString &tournamentId) const = 0;
    virtual ByteArray fromTournament(const int &index) const = 0;
    virtual ByteArray fromTournaments() const = 0;
};
#endif // ICREATEJSONFROMDARTSINPUT_H
