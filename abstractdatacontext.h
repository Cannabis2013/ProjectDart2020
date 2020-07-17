#ifndef ABSTRACTDATACONTEXT_H
#define ABSTRACTDATACONTEXT_H

#include <qobject.h>

#include "idatacontext.h"
#include "modelbuildercollection.h"

typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;

class AbstractDataContext : public QObject, public DefaultDataInterface
{
    Q_OBJECT
public:

signals:
    void sendPlayerScore(const QUuid &playerID, const int &score);


};

#endif // ABSTRACTDATACONTEXT_H
