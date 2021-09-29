#ifndef ICREATEJSONFROMMODELS_H
#define ICREATEJSONFROMMODELS_H

#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include <qvector.h>


class ICreateJsonFromModels
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*>& model) const = 0;
};

#endif // ICREATEJSONFROMDARTSINPUT_H
