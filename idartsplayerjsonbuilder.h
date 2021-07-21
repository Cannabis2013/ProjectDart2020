#ifndef IDARTSPLAYERJSONBUILDER_H
#define IDARTSPLAYERJSONBUILDER_H

#include "iplayerjsonbuilder.h"
#include <quuid.h>
#include <qbytearray.h>
#include "iplayermodel.h"

class IDartsPlayerJsonBuilder : public IPlayerJsonBuilder<IModel<QUuid>,QUuid,QString, QByteArray>
{};
#endif // ICREATEJSONFROMDARTSPLAYERCREDENTIALS_H
