#ifndef IDARTSPLAYERBUILDERSERVICE_H
#define IDARTSPLAYERBUILDERSERVICE_H

#include <qvector.h>

template<typename TPlayerInterface, typename TJsonFormat>
class IDartsPlayerBuilderService
{
public:
    typedef TPlayerInterface PlayerInterface;
    typedef TJsonFormat JsonFormat;
    virtual const PlayerInterface* buildPlayerModelByJson(const JsonFormat& json) const = 0;
    virtual QVector<const PlayerInterface*> buildPlayerModelsByJson(const JsonFormat& json) = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
