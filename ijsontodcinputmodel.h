#ifndef IJSONTODCINPUTMODEL_H
#define IJSONTODCINPUTMODEL_H

#include "idcinputmodel.h"
#include <qbytearray.h>
class IJsonToDCInputModel
{
public:
    virtual const DCContext::IDCInputModel *toModel(const QByteArray &json) const = 0;
};

#endif // IDCJSONTOINPUT_H
