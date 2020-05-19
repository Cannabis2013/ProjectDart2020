#ifndef CONSOLEUSERINTERFACE_H
#define CONSOLEUSERINTERFACE_H

#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "ProjectDartInterface.h"

typedef ProjectDartInterface<QUuid,QString,QList<QUuid>> DefaultDartInterface;

class ConsoleUserInterface
{
public:
    ConsoleUserInterface();

    ConsoleUserInterface *setDartInterface(DefaultDartInterface *interface)
    {
        _dartInterface = interface;

        return this;
    }
    const DefaultDartInterface *dartInterface() const
    {
        return _dartInterface;
    }

private:

    DefaultDartInterface *_dartInterface;
};

#endif // CONSOLEUSERINTERFACE_H
