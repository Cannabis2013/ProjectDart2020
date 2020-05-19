#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "ProjectDartInterface.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

typedef ProjectDartInterface<QUuid,QString,QList<QUuid>> DefaultProjectDartInterface;

class ProjectDart : public DefaultProjectDartInterface
{
};

#endif // PROJECTDART_H
