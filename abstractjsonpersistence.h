#ifndef ABSTRACTJSONPERSISTENCE_H
#define ABSTRACTJSONPERSISTENCE_H

#include <qdatastream.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include "ipersistence.h"

class AbstractJSONPersistence : public IPersistence
{
protected:
    void writeJsonObjectToFile(const QJsonObject &json, const QString &fileName);
    QJsonObject readJsonObjectFromFile(const QString &fileName);
};

#endif // ABSTRACTJSONPERSISTENCE_H
