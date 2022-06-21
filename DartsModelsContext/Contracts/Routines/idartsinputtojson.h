#ifndef IDARTSINPUTTOJSON_H
#define IDARTSINPUTTOJSON_H

class DartsModelsServices;
class QString;
class QUuid;
class QByteArray;

template<typename TModel>
class IDartsInputToJson
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    virtual ByteArray toJson(const QUuid &tournamentID, const QString &name,const ByteArray &idxBa, const DartsModelsServices *services) const = 0;
};

#endif // IDARTSGETINPUT_H
