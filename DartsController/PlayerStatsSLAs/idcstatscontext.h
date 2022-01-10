#ifndef IDCSTATSCONTEXT_H
#define IDCSTATSCONTEXT_H
template<typename T>
class QVector;
struct DCInput;
struct DCPlayerStats;
class QString;
class QStringList;
class IDCStatsContext
{
public:
    virtual void setPlayers(const QStringList &players) = 0;
    virtual DCPlayerStats &stat(const QString &name) = 0;
    virtual QVector<DCPlayerStats> &stats() = 0;
    virtual void reset() = 0;
    virtual void update(const DCInput &input) = 0;
    virtual void update(const QVector<DCInput> &inputs) = 0;
};
#endif // IDCSTATSBUILDER_H
