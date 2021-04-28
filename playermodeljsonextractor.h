#ifndef PLAYERMODELJSONEXTRACTOR_H
#define PLAYERMODELJSONEXTRACTOR_H

#include "iplayerjsonextractorservice.h"
#include <qjsonarray.h>
#include <playermodel.h>
#include <qjsonobject.h>
#include <qvector.h>

class PlayerModelJsonExtractor : public IPlayerJsonExtractorService<QJsonArray,QVector<const IModel<QUuid>*>>
{
    // IPlayerJsonExtractorService interface
public:
    QVector<const IModel<QUuid>*> extractPlayerModelsFromJsonArray(const QJsonArray& arr);
};

#endif // PLAYERMODELJSONEXTRACTOR_H
