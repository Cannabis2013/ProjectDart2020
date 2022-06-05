#ifndef GETTOURNAMENTSASJSON_H
#define GETTOURNAMENTSASJSON_H

#include <DartsModelsContext/Routines/igettournamentsasjson.h>

template<typename T> class QVector;
template<typename T> class IModel;
class QUuid;
class QJsonArray;
class QByteArray;
class DartsModelsServices;

class GetTournamentsAsJson : public IGetTournamentsAsJson
{
public:
    QByteArray tournamentsToJson(const DartsModelsServices *services) const override;
private:
    QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models, const DartsModelsServices *services) const;
    QByteArray toByteArray(const QJsonArray &arr) const;
};

#endif // GETTOURNAMENTSASJSON_H
