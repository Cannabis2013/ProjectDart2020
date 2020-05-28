#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "abstractdartinterface.h"
#include "ipointlogisticmanager.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

typedef IDataContext<QUuid, QList<QUuid>,QString> DefaultDataContext;
typedef IGameController<QUuid,QString, DefaultDataContext> DefaultGameController;

class ProjectDart : public AbstractDartInterface
{
private:

    DefaultDataContext *_dataContext;
    DefaultGameController *_gameController;
};

#endif // PROJECTDART_H
