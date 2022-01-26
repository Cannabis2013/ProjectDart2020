#ifndef IDCSTATISTICS_H
#define IDCSTATISTICS_H
struct DCPlayer;
struct DCInput;
template<typename T>
class QVector;
struct DCStatsModel;
class QString;
class QStringList;
class IDCStatistics
{
public:
    typedef QVector<DCPlayer> Players;
    virtual void setPlayers(const Players &players) = 0;
    virtual DCStatsModel &stat(const QString &name) = 0;
    virtual QVector<DCStatsModel> &stats() = 0;
    virtual void reset() = 0;
    virtual void update(const DCInput &input) = 0;
    virtual void update(const QVector<DCInput> &inputs) = 0;
};
#endif // IDCSTATSBUILDER_H
