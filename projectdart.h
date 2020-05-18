#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "ProjectDartInterface.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

class ProjectDart : public ProjectDartInterface<QUuid,QString,QList<QUuid>>
{
public:
    ProjectDart();
};

#endif // PROJECTDART_H
