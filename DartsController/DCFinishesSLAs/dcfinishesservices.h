#ifndef DCFINISHESSERVICES_H
#define DCFINISHESSERVICES_H
#include "idcfinishbuilder.h"
class DCFinishesSLAs
{
public:
    IDCFinishBuilder *finishBuilder() const {return _suggestFinishes;}
    void setFinishBuilder(IDCFinishBuilder *service) {_suggestFinishes = service;}
private:
    IDCFinishBuilder *_suggestFinishes = nullptr;
};

#endif // DCFINISHESSERVICES_H
