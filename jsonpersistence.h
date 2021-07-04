#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include <qdatastream.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

class JSONPersistence
{
protected:
    void writeJsonObjectToFile(const QByteArray &json, const QString &fileName);
    QByteArray readJsonObjectFromFile(const QString &fileName);
};

#endif // ABSTRACTJSONPERSISTENCE_H
