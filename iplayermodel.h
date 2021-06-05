#ifndef IMODEL_H
#define IMODEL_H

#include "imodel.h"
#include <quuid.h>
#include <qstring.h>
namespace DartsModelsContext {
    class IPlayerModel : public IModel<QUuid,QByteArray>
    {
    public:
        virtual QString playerName() const = 0;

        virtual IPlayerModel* setUserName(const QString &name) = 0;

        virtual QString email() const = 0;
        virtual IPlayerModel* setEmail(const QString& email) = 0;

        virtual int userRole() const = 0;
        virtual IPlayerModel* setUserRole(const int& role) = 0;

        virtual bool operator==(IPlayerModel* &other) = 0;
    };
}

#endif // IMODEL_H
