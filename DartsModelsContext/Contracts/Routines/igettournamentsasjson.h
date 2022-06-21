#ifndef IGETTOURNAMENTSASJSON_H
#define IGETTOURNAMENTSASJSON_H

class QByteArray;
class DartsModelsServices;

class IGetTournamentsAsJson
{
public:
    virtual QByteArray tournamentsToJson(const DartsModelsServices *services) const = 0;
};

#endif // IGETTOURNAMENTSASJSON_H
