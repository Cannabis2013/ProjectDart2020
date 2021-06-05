#ifndef IPLAYERMODELJSONSERVICE_H
#define IPLAYERMODELJSONSERVICE_H

#include <qvector.h>

template<typename TModelInterface, typename TUuid, typename  TString, typename TJsonFormat>
class IPlayerModelsJsonService
{
public:
    typedef TModelInterface PlayerInterface;
    typedef TUuid IdFormat;
    typedef TString StringFormat;
    typedef TJsonFormat JsonFormat;
    virtual QVector<int> getPlayerIndexesByJson(const JsonFormat&) const = 0;
    virtual JsonFormat assembleJsonFromPlayerNamesAndIds(const QVector<IdFormat>&, const QVector<StringFormat>&) const = 0;
    virtual JsonFormat assembleJsonByPlayerIdAndName(const IdFormat&,const QString&) const = 0;
    virtual int getDeletePlayerIndexFromJson(const JsonFormat&) const = 0;
    virtual const PlayerInterface* assemblePlayerModelFromJson(const JsonFormat&) const = 0;
    virtual IdFormat getWinnerIdByJson(const JsonFormat&) const = 0;
};

#endif // IPLAYERMODELJSONSERVICE_H
