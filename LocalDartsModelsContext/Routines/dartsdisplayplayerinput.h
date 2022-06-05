#ifndef DARTSDISPLAYPLAYERINPUT_H
#define DARTSDISPLAYPLAYERINPUT_H

#include <DartsModelsContext/Routines/idartsrevealinput.h>

class IDartsIndex;
template<typename T> class IModel;

class DartsDisplayPlayerInput : public IDartsRevealInput<IModel<QUuid>>
{
public:

    virtual bool display(QUuid tournamentID, QString name, const QByteArray &indexAsByteArray, DartsModelsServices *services) override;
private:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayedHint = 0x2,
        allHints = HiddenHint | DisplayedHint
    };
    Model *getInputModel(QUuid tournamentID, QString name, IDartsIndex *index, DartsModelsServices *services);
    void updateInputHint(Model *model);
    Model *getTournamentModel(QUuid tournamentID, DartsModelsServices *services);
    void updateTournamentIndexes(IDartsIndex *index, IModel<QUuid> *model);
    bool persistChanges(DartsModelsServices *services);
};

#endif // DARTSREVEALPLAYERINPUT_H
