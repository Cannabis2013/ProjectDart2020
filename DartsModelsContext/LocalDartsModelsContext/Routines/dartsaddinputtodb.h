#ifndef DARTSADDINPUTTODB_H
#define DARTSADDINPUTTODB_H

#include <DartsModelsContext/Contracts/Routines/idartsaddinputtodb.h>

class IDartsTournament;
class IDartsIndex;
template<typename T> class IModel;
class QUuid;

class DartsAddInputToDb : public IDartsAddInputToDb
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    typedef IModel<QUuid> Model;
    bool add(const ByteArray &inputAsByteArray,
             const ByteArray &indexAsByteArray,
             const QUuid &tournamentID,
             DartsModelsServices *services) override;
private:
    void addInputToDb(const QByteArray &inputAsByteArray, DartsModelsServices *services);
    void updateTournamentIndex(const QByteArray &indexAsByteArray, const QUuid &tournamentID, DartsModelsServices *services);
    IDartsTournament *getTournamentModel(const QUuid &tournamentID, DartsModelsServices *services);
    void updateTournament(IDartsTournament *tournament, IDartsIndex *index) const;
    Model *createInput(const ByteArray &byteArray, DartsModelsServices *services) const;
    void removeHiddenInputs(const QUuid &tournamentID, DartsModelsServices *services) const;
    bool persistChanges(DartsModelsServices *services);
};

#endif // DARTSADDINPUTTODB_H
