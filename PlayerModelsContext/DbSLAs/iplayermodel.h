#ifndef IMODEL_H
#define IMODEL_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <quuid.h>
#include <qstring.h>
class IPlayerModel : public IModel<QUuid>
{
public:
    virtual QString name() const = 0;
    virtual IPlayerModel* setName(const QString &name) = 0;
    virtual QString email() const = 0;
    virtual IPlayerModel* setEmail(const QString& email) = 0;
    virtual bool operator==(IPlayerModel* &other) = 0;
};
#endif // IMODEL_H
