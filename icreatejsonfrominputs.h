#ifndef ICREATEJSONFROMINPUTS_H
#define ICREATEJSONFROMINPUTS_H

#include "icreatejsonfrom.h"
#include "iplayerinput.h"
#include <qvector.h>

class ICreateJsonFromInputs : public ICreateJsonFrom<const QVector<const IModel<QUuid>*>&,QByteArray>
{
public:
    virtual QByteArray createJson(const QVector<const IModel<QUuid>*>& model) const override = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
