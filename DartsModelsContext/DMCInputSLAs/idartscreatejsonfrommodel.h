#ifndef IDARTSCREATEJSONFROMMODEL_H
#define IDARTSCREATEJSONFROMMODEL_H

#include <qbytearray.h>

template <typename TModel, typename TJson = QByteArray>
class IDartsCreateJsonFromModel
{
public:
    virtual TJson createJson(const TModel *model) const = 0;
};

#endif // IDARTSCREATEJSON_H
