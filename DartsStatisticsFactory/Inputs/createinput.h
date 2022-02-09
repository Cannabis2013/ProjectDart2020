#ifndef CREATEINPUT_H
#define CREATEINPUT_H
#include "Inputs/icreateinput.h"
struct SnapShot;
class CreateInput : public ICreateInput<SnapShot>
{
public:
    virtual Ipt create(const QString &name, const int &score, const int &modCode) const override;
};

#endif // CREATEINPUT_H
