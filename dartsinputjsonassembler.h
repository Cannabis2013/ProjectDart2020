#ifndef DARTSINPUTJSONASSEMBLER_H
#define DARTSINPUTJSONASSEMBLER_H

#include "iunaryservice.h"

#include <QByteArray>
#include "imodel.h"
#include <quuid.h>

#include "dartsscoreinput.h"
#include "dartspointinput.h"

#include <qjsonobject.h>
#include <qjsonarray.h>

namespace InputAssemblerContext {
    typedef QVector<const IDartsPointInput<QUuid>*> modelsList;
}

class DartsPointsJsonAssembler :
        public IUnaryService<const InputAssemblerContext::modelsList&,QJsonArray>
{
public:

    QJsonArray service(const InputAssemblerContext::modelsList& modelsList) override;
};

#endif // DARTSINPUTJSONASSEMBLER_H
