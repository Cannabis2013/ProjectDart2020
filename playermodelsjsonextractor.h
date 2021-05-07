#ifndef PLAYERMODELJSONEXTRACTOR_H
#define PLAYERMODELJSONEXTRACTOR_H

#include "iunaryservice.h"
#include <qjsonarray.h>
#include <playermodel.h>
#include <qjsonobject.h>
#include <qvector.h>

class PlayerModelsJsonExtractor :
        public IUnaryService<const QJsonArray&,QVector<const IPlayerModel*>>
{
public:
    static PlayerModelsJsonExtractor* createInstance();
    QVector<const IPlayerModel*> service(const QJsonArray& arr);
};

#endif // PLAYERMODELJSONEXTRACTOR_H
