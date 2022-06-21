#ifndef IDCGETSCORESASJSON_H
#define IDCGETSCORESASJSON_H
class QByteArray;
class IDCGetScoresAsJson
{
public:
    virtual QByteArray get() const = 0;
};

#endif // IDCGETSCORESASJSON_H
