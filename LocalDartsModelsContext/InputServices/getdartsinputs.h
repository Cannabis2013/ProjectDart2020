#ifndef GETDARTSINPUTS_H
#define GETDARTSINPUTS_H

#include <DartsModelsContext/InputsDbSLAs/igetinputs.h>

template<typename T>
class IModel;

class GetDartsInputs : public IGetInputs<IModel<QUuid>,IDartsIndex, DartsMetaModel>
{
public:
        enum ModelDisplayHint{
                HiddenHint = 0x1,
                DisplayHint = 0x2,
                allHints = HiddenHint | DisplayHint
        };
        Model *get(const DartsMetaModel &meta, const IDartsIndex *index, const Models &models) const override;
        Models get(const QUuid &tournamentId, const Models &models) const override;
        virtual Models getHidden(const QUuid &tournamentId, const Models &models) const override;
        virtual Models getDisplayed(const QUuid &tournamentId, const Models &models) const override;
private:
        Models getModels(const QUuid &tournamentId, const Models &models) const;
        Models getModels(const int &hint, const Models &models) const;
};
#endif // GETINPUTMODELSSERVICE_H
