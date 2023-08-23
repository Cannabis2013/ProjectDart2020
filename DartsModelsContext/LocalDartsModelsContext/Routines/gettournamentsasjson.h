#ifndef GETTOURNAMENTSASJSON_H
#define GETTOURNAMENTSASJSON_H

#include <DartsModelsContext/Contracts/Model/imodel.h>
#include <DartsModelsContext/Contracts/Routines/igettournamentsasjson.h>
#include <qjsonarray.h>
#include <quuid.h>

class GetTournamentsAsJson : public IGetTournamentsAsJson {
public:
      QByteArray tournamentsToJson(
          const DartsModelsServices *services) const override;

private:
      QJsonArray toJsonArray(const QVector<IModel<QUuid> *> &models,
                             const DartsModelsServices *services) const;
      QByteArray toByteArray(const QJsonArray &arr) const;
};

#endif // GETTOURNAMENTSASJSON_H
