#ifndef IDARTSCREATEJSONFROMSCORES_H
#define IDARTSCREATEJSONFROMSCORES_H

#include "icreatejsonfrom.h"
#include <qvector.h>
#include "iplayerinput.h"
class IDartsCreateJsonFromScores : public ICreateJsonFrom<const QVector<const IPlayerInput*>&>
{
public:
    virtual QByteArray createJson(const QVector<const IPlayerInput*>&) const override = 0;
};

#endif // IDARTSSCOREJSONSERVICE_H
