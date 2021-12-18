#ifndef DARTWINNERMODELBUILDER_H
#define DARTWINNERMODELBUILDER_H
#include "TournamentsSLAs/iwinnerinfobuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class DartWinnerModelBuilder : public IWinnerInfoBuilder
{
public:
    virtual DataModel create(const QByteArray &json) const override;
private:
    DataModel toModel(const QJsonObject &obj) const;
    QJsonObject toJsonObject(const QByteArray &json) const;
};

#endif // GETDARTSTOURNAMENTDATAFROMJSON_H
