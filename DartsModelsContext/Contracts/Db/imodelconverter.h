#ifndef IMODELCONVERTER_H
#define IMODELCONVERTER_H

#include <qjsonobject.h>

class IDartsInputBuilder;

template <typename TModel>

class IModelConverter {
public:
        typedef TModel Model;
        typedef QByteArray ByteArray;
        typedef QJsonObject Json;
        virtual Json convert(Model *model) const = 0;
        virtual Model *convert(const ByteArray &byteArray) const = 0;
        virtual Model *convert(const Json &d) const = 0;
};
#endif // IJSONBUILDER_H
