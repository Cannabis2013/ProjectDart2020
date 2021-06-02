#ifndef DARTSINPUTJSONASSEMBLER_H
#define DARTSINPUTJSONASSEMBLER_H

#include "iunaryservice.h"
#include <QByteArray>
#include "imodel.h"
#include <quuid.h>
#include "dartspointinput.h"
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsModelsContext {
    typedef QVector<const IModel<QUuid,QByteArray>*> ModelsList;
    class AssembleJsonArrayFromDartsPoints :
            public IUnaryService<const ModelsList&,QJsonArray>
    {
    public:
        QJsonArray service(const ModelsList& modelsList) override;
    };
}

#endif // DARTSINPUTJSONASSEMBLER_H
