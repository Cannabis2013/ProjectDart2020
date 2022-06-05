#ifndef CREATEINPUT_H
#define CREATEINPUT_H

#include <DartsStatistics/Inputs/icreatesnapshot.h>

struct SnapShot;

class CreateInput : public ICreateSnapShot<SnapShot>
{
public:
    virtual Ipt create(const QString &name, const int &score, const int &modCode) const override;
};

#endif // CREATEINPUT_H
