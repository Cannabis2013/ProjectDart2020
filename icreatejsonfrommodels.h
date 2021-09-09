#ifndef ICREATEJSONFROMMODELS_H
#define ICREATEJSONFROMMODELS_H

#include "itojson.h"
#include "iplayerinput.h"
#include <qvector.h>


class ICreateJsonFromModels : public IToJson<const QVector<const IModel<QUuid>*>&,QByteArray>
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*>& model) const override = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
