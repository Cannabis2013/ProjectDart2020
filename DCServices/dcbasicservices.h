#ifndef DCBASICSERVICES_H
#define DCBASICSERVICES_H
#include "DCInputsSLA/idartsinputfinishes.h"
#include "idcwinnerservice.h"
#include "idcinputstojson.h"
#include "DCIndexSLA/idcindexesbuilder.h"
#include "idcplayermodelbuilder.h"
#include "idcinitialscore.h"
#include "DCInputsSLA/idartsinputvalidator.h"
#include "DCServices/idartsdeterminestatusbyid.h"
class DCBasicServices
{
public:
    typedef QVector<const DCContext::IDCInputModel*> DartsScores;
    typedef QVector<const DCContext::IDCPlayer*> DartsPlayers;
    IDartsDetermineStatusById *determineStatusById() const
    {
        return _determineStatusById;
    }
    void setDetermineStatusById(IDartsDetermineStatusById *newDetermineStatusById)
    {
        _determineStatusById = newDetermineStatusById;
    }
private:
    IDartsDetermineStatusById* _determineStatusById;
};
#endif // DSCSERVICESPROVIDER_H
