#ifndef DARTSADDINPUTTODB_H
#define DARTSADDINPUTTODB_H
#include "Routines/idartsaddinputtodb.h"
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
    bool add(const ByteArray &byteArray, const QUuid &tournamentID, DartsModelsServices *services) override;
private:
    Model *createInput(const ByteArray &byteArray, DartsModelsServices *services) const;
    void removeHiddenInputs(const QUuid &tournamentID, DartsModelsServices *services) const;
};

#endif // DARTSADDINPUTTODB_H
