#ifndef IDSCMODELBUILDER_H
#define IDSCMODELBUILDER_H

#include <idcplayer.h>
#include <qvector.h>

class IDCPlayerModelBuilder
{
public:
    virtual const DCContext::IDCPlayer* createModel(const QByteArray& json) const = 0;
    virtual const DCContext::IDCPlayer* createModel(const QUuid &id, const QString &stringValue) const = 0;
    virtual QVector<const DCContext::IDCPlayer*> createModels(const QByteArray& json) = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
