#ifndef DCEXTERNALINPUTSERVICE_H
#define DCEXTERNALINPUTSERVICE_H
#include "DCInputSLAs/idcexternaliptservice.h"
class DCIndex;
class DCServices;
class DCExternalInputService : public IDCExternalIptService
{
public:
    DCExternalInputService(DCServices *services);
    DCInput getPreviousInput() override;
    DCInput getCurrentInput() override;
    void hideInput() override;
    void displayInput() override;
private:
    DCInput getInput(const DCIndex &index);
    DCServices *_services;
};

#endif // DCGETINPUT_H
