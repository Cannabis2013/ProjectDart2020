#ifndef DARTSCONVERTTOJSON_H
#define DARTSCONVERTTOJSON_H
#include "TournamentsDbSLAs/itournamentjsonbuilder.h"
template<typename T> class IDbContext;
template<typename T> class IModelConverter;
class QJsonArray;
class DMCServices;
class DartsConvertToJson : public IDartsJsonBuilder<IModel<QUuid>>
{
public:
    typedef IModelConverter<Model> ModelConverter;
    typedef IDbContext<Model> DbContext;
    DartsConvertToJson(DMCServices *services);
    QByteArray fromTournament(const QUuid &ID) const override;
    QByteArray fromTournament(const QString &ID) const override;
    ByteArray fromTournament(const int &index) const override;
    QByteArray fromTournaments() const override;
private:
    Model *getTournamentByID(const QUuid &ID) const;
    QJsonObject fromByteArray(const QByteArray &byteArray) const;
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models) const;
    QByteArray toByteArray(const QJsonObject &obj) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
    DMCServices *_services;
    ModelConverter *_cvtr;
    DbContext *_dartsDb;
};
#endif // ASSEMBLEJSONFROMDARTSTOURNAMENTMODELS_H
