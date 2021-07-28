#ifndef ICREATEJSONFROMMODELS_H
#define ICREATEJSONFROMMODELS_H

#include "icreatejsonfrom.h"
#include "iplayerinput.h"
#include <qvector.h>


class ICreateJsonFromModels : public ICreateJsonFrom<const QVector<const IModel<QUuid>*>&,QByteArray>
{
public:
    virtual QByteArray createJson(const QVector<const IModel<QUuid>*>& model) const override = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
