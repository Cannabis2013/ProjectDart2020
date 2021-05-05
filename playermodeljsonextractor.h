#ifndef PLAYERMODELJSONEXTRACTOR_H
#define PLAYERMODELJSONEXTRACTOR_H

#include "iunaryservice.h"
#include <qjsonarray.h>
#include <playermodel.h>
#include <qjsonobject.h>
#include <qvector.h>

class PlayerModelJsonExtractor :
        public IUnaryService<const QJsonArray&,QVector<const IModel<QUuid>*>>
{
    // IPlayerJsonExtractorService interface
public:
    QVector<const IModel<QUuid>*> service(const QJsonArray& arr);
};

#endif // PLAYERMODELJSONEXTRACTOR_H
