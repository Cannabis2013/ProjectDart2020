#ifndef IDCGETINPUT_H
#define IDCGETINPUT_H
class DCInput;
class IDCGetInput
{
public:
    virtual DCInput getPreviousInput() = 0;
    virtual DCInput getCurrentInput() = 0;
};

#endif // IDCGETINPUT_H
