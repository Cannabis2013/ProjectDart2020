#ifndef DARTSINPUTJSONASSEMBLER_H
#define DARTSINPUTJSONASSEMBLER_H

#include "idartsinputassembler.h"

#include <QByteArray>
#include "imodel.h"
#include <quuid.h>

#include "dartsscoreinput.h"
#include "dartspointinput.h"

#include <qjsonobject.h>
#include <qjsonarray.h>

namespace InputAssemblerContext {
    typedef QVector<const IModel<QUuid>*> modelsList;
}

class DartsInputJsonAssembler : public IDartsInputAssembler<QJsonArray,InputAssemblerContext::modelsList>
{
    // IDartsInputAssembler interface
public:

    QJsonArray assembleDartsPointJson(const InputAssemblerContext::modelsList& modelsList);
    QJsonArray assembleDartsScoreJson(const InputAssemblerContext::modelsList& modelsList);
};

#endif // DARTSINPUTJSONASSEMBLER_H
