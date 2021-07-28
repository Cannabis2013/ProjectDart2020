#ifndef IDARTSPLAYERBUILDERSERVICE_H
#define IDARTSPLAYERBUILDERSERVICE_H

#include <qvector.h>

template<typename TPlayerInterface, typename TUuid,
         typename TString, typename TJsonFormat>
class IDartsPlayerBuilderService
{
public:
    typedef TPlayerInterface PlayerInterface;
    typedef TUuid IdFormat;
    typedef TString StringFormat;
    typedef TJsonFormat JsonFormat;
    virtual const PlayerInterface* createModel(const JsonFormat& json) const = 0;
    virtual QVector<const PlayerInterface*> createModels(const JsonFormat& json) = 0;
    virtual const PlayerInterface* createPlayerModelByValues(const IdFormat &id, const StringFormat &name) const = 0;
};

#endif // IDARTSPLAYERBUILDERSERVICE_H
