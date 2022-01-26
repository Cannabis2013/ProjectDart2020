#ifndef DCGETINPUT_H
#define DCGETINPUT_H
#include "DCInputSLAs/idcgetinput.h"
class DCIndex;
class DCServices;
class DCGetInput : public IDCGetInput
{
public:
    DCGetInput(DCServices *services);
    virtual DCInput getPreviousInput() override;
    virtual DCInput getCurrentInput() override;
private:
    DCInput getInput(const DCIndex &index);
    DCServices *_services;
};

#endif // DCGETINPUT_H
