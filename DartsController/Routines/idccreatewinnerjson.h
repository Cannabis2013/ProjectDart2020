#ifndef IDCCREATEWINNERJSON_H
#define IDCCREATEWINNERJSON_H
class QByteArray;
class IDCCreateWinnerJson
{
public:
    virtual QByteArray create() const = 0;
};

#endif // IDCCREATEWINNERJSON_H
