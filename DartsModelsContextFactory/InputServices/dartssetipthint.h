#ifndef DARTSSETIPTHINT_H
#define DARTSSETIPTHINT_H
#include "InputSLAs/IDartsSetIptHint.h"

class IDartsIndex;
template<typename T> class IDartsIdxBuilder;
template<typename T> class IDbContext;
class DartsInputServices;
class DartsModelsServices;
class QUuid;
template<typename T> class IModel;
class DartsSetIptHint : public IDartsSetIptHint<IModel<QUuid>>
{
public:
    typedef IDartsIdxBuilder<IDartsIndex> IdxBuilder;
    typedef IDbContext<Model> DbContext;
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    DartsSetIptHint(DartsModelsServices *services);
    virtual void setHidden(QUuid tournamentID, QString name, const QByteArray &idxBa) const override;
    virtual void setVisible(QUuid tournamentID, QString name, const QByteArray &idxBa) const override;
    void setVisible(Model *input) const override;
private:
    void setHint(Model *model, const ModelDisplayHint &hint) const;
    DartsModelsServices *_services;
    DartsInputServices *_iptServices;
    DbContext *_iptsDb;
    IdxBuilder *_idxCvtr;
};
#endif // DARTSSETIPTHINT_H
