#ifndef EXTRACTWINNERINFOFROMJSON_H
#define EXTRACTWINNERINFOFROMJSON_H

#include "DartsModelsContext/DMCTournamentSLAs/iextractwinnerinfo.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class ExtractWinnerInfoFromJson : public IExtractWinnerInfo
{
public:
    virtual DataModel createWinnerDataModel(const QByteArray &json) const override;
private:
    DataModel createDataModelFromObject(const QJsonObject &obj) const;
    QJsonObject createJsonObject(const QByteArray &json) const;
};

#endif // GETDARTSTOURNAMENTDATAFROMJSON_H
