#ifndef DARTSHIDEPLAYERINPUT_H
#define DARTSHIDEPLAYERINPUT_H

#include "Routines/IDartsHideInput.h"

class IDartsIndex;
class QUuid;

template<typename T> class IModel;
class DartsHidePlayerInput : public IDartsHideInput<IModel<QUuid>>
{
public:
    typedef IModel<QUuid> Model;
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual bool hide(QUuid tournamentID, QString name, const QByteArray &idxBa, DartsModelsServices *services) override;
private:
    Model *getInputModel(QUuid tournamentID, QString name, IDartsIndex *index, DartsModelsServices *services);
    void updateInputHint(Model *model);
    Model *getTournamentModel(QUuid tournamentID, DartsModelsServices *services);
    void updateTournamentIndexes(IDartsIndex *index, IModel<QUuid> *model);
    bool persistChanges(DartsModelsServices *services);
};
#endif // DARTSSETIPTHINT_H
