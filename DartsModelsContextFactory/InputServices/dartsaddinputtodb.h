#ifndef DARTSADDINPUTTODB_H
#define DARTSADDINPUTTODB_H
#include "InputSLAs/idartsaddinputtodb.h"
template<typename T> class IDbContext;
template<typename T> class IModel;
class QUuid;
class DartsInputServices;
class DartsModelsServices;
class DartsAddInputToDb : public IDartsAddInputToDb
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    typedef IModel<QUuid> Model;
    DartsAddInputToDb(DartsModelsServices *services);
    void add(const ByteArray &byteArray, const QUuid &tournamentID) override;
private:
    Model *createInput(const ByteArray &byteArray) const;
    void removeHiddenInputs(const QUuid &tournamentID) const;
    DartsModelsServices *_services;
    DartsInputServices *_iptServices;
    IDbContext<Model> *_iptsDb;
};

#endif // DARTSADDINPUTTODB_H
