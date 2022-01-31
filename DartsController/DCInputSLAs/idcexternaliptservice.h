#ifndef IDCEXTERNALIPTSERVICE_H
#define IDCEXTERNALIPTSERVICE_H
class DCInput;
class IDCExternalIptService
{
public:
    virtual DCInput getPreviousInput() = 0;
    virtual DCInput getCurrentInput() = 0;
    virtual void hideInput() = 0;
    virtual void displayInput() = 0;
};

#endif // IDCGETINPUT_H
