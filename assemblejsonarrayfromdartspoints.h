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

class AssembleJsonArrayFromDartsPoints :
        public IUnaryService<const QVector<const IDartsPointInput<QUuid>*>&,QJsonArray>
{
public:

    QJsonArray service(const QVector<const IDartsPointInput<QUuid>*>& modelsList) override;
};

#endif // DARTSINPUTJSONASSEMBLER_H
