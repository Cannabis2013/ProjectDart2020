#ifndef DCINPUTBUILDER_H
#define DCINPUTBUILDER_H
#include "Inputs/idcinputbuilder.h"
class QJsonDocument;
class QJsonObject;
class QByteArray;
class DCInput;
class DCInputBuilder : public IDCInputBuilder<DCInput>
{
public:
    typedef QJsonDocument Doc;
    virtual Model create() const override;
    virtual Model create(const QString &name, const int &remainingScore) const override;
};
#endif // DCINPUTCONVERTER_H
