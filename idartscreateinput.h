#ifndef IDARTSCREATEINPUT_H
#define IDARTSCREATEINPUT_H

#include "iplayerinput.h"
class IDartsCreateInput
{
public:
    virtual const IPlayerInput *create(const QByteArray &json) const = 0;
};

#endif // IDARTSINPUTBUILDER_H
