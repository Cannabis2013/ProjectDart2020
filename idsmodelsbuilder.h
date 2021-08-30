#ifndef IDARTSSCOREMODELSBUILDERSERVICE_H
#define IDARTSSCOREMODELSBUILDERSERVICE_H

#include <idcplayer.h>
#include <idscmodel.h>
#include <idscmodel.h>
#include <qvector.h>
#include "idcscoresservice.h"
class IDSModelsBuilder
{
public:
    virtual DSCContext::IDSCModel* createScoreModel(const QByteArray& json) const = 0;
    virtual DSCContext::IDSCModel* createScoreModel(const int& score) const = 0;
    virtual QVector<DSCContext::IDSCModel*> createScoreModels(IDCScoresService* scoresService) const = 0;
    virtual QVector<DSCContext::IDSCModel*> createScoreModels(const QByteArray& json) const = 0;
};
#endif // IDARTSSCOREMODELSBUILDERSERVICE_H
