#ifndef DARTSINPUTJSONASSEMBLER_H
#define DARTSINPUTJSONASSEMBLER_H

#include "iunaryservice.h"
#include <QByteArray>
#include "imodel.h"
#include <quuid.h>
#include "dartspointinput.h"
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace InputAssemblerContext {
    typedef QVector<const DartsModelsContext::IDartsPointInput*> modelsList;
}

class AssembleJsonArrayFromDartsPoints :
        public IUnaryService<const QVector<const DartsModelsContext::IDartsPointInput*>&,QJsonArray>
{
public:

    QJsonArray service(const QVector<const DartsModelsContext::IDartsPointInput*>& modelsList) override;
};

#endif // DARTSINPUTJSONASSEMBLER_H
