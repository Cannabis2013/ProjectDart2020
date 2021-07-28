#ifndef DARTSCREATEJSONMETADATA_H
#define DARTSCREATEJSONMETADATA_H

#include "idartscreatejsonmetadata.h"
#include "iplayermodel.h"

class DartsCreateJsonMetaData : public IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *model,
                                               const IDartsTournamentJsonBuilder *jsonBuilder) const override
    {
        auto json = jsonBuilder->createJson(model);
        return json;
    }
private:
    QString getWinnerNameFromModel(const IModel<QUuid> *model) const
    {
        if(model != nullptr)
            return dynamic_cast<const PlayersContext::IPlayerModel*>(model)->playerName();
        else
            return "";
    }
};
#endif // CREATEDARTSMETADATA_H
