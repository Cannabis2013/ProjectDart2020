#ifndef DCFINISHESSERVICES_H
#define DCFINISHESSERVICES_H
#include "idcfinishbuilder.h"

#include <DartsController/LocalDartsController/Finishes/dcfinishbuilder.h>
class DCFinishServices
{
public:
    IDCFinishBuilder *finishBuilder() const {return _suggestFinishes;}
    void setFinishBuilder(IDCFinishBuilder *service) {_suggestFinishes = service;}
private:
    IDCFinishBuilder *_suggestFinishes = new DCFinishBuilder();
};

#endif // DCFINISHESSERVICES_H
