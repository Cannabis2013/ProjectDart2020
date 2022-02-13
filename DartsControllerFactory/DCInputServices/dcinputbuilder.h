#ifndef DCINPUTBUILDER_H
#define DCINPUTBUILDER_H
#include "DCInputSLAs/idcinputbuilder.h"
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
    virtual Model create(const Json &json, const int &remainingScore) const override;
    virtual Json create(const Model &model) const override;
    virtual Model create(const Json &json) const override;
private:
    QJsonObject toJson(const Model &model) const;
    QJsonObject toJson(const ByteArray &byteArray) const;
    Model toModel(const Json &json, const int &remainingScore = -1) const;

};
#endif // DCINPUTCONVERTER_H
