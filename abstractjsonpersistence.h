#ifndef ABSTRACTJSONPERSISTENCE_H
#define ABSTRACTJSONPERSISTENCE_H

#include "persistenceinterface.h"
#include <qdatastream.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

class AbstractJSONPersistence : public PersistenceInterface
{
public:
    AbstractJSONPersistence();

protected:
    void writeJSONToFile(const QJsonObject &json, const QString &fileName);
    QJsonObject readJSONFromFile(const QString &fileName);
};

#endif // ABSTRACTJSONPERSISTENCE_H
