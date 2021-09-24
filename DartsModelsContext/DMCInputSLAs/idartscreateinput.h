#ifndef IDARTSCREATEINPUT_H
#define IDARTSCREATEINPUT_H

#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
class IDartsCreateInput
{
public:
    virtual const IPlayerInput *create(const QByteArray &json) const = 0;
};

#endif // IDARTSINPUTBUILDER_H
