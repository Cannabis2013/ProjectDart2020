#ifndef IDCGETTURNVALUESASJSON_H
#define IDCGETTURNVALUESASJSON_H
class QByteArray;
class IDCGetTurnValuesAsJson
{
public:
    virtual QByteArray toJson() const = 0;
};

#endif // IDCGETTURNVALUES_H
