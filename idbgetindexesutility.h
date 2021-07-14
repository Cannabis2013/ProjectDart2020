#ifndef IDBGETINDEXESUTILITY_H
#define IDBGETINDEXESUTILITY_H
#include <qvector.h>
class IDbGetIndexesUtility
{
public:
    virtual int dbIndexFromJson(const QByteArray &json) const = 0;
    virtual QVector<int> dbIndexesFromJson(const QByteArray &json) const = 0;
};
#endif // IDARTSUTILITYSERVICE_H
