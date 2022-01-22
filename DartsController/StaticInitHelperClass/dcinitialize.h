#ifndef DCINITPLAYERSCORES_H
#define DCINITPLAYERSCORES_H
class QStringList;
template<typename T>
class QVector;
struct DCInput;
struct DCMeta;
struct DCPlayer;
class IDCIndexController;
class IDCMetaContext;
class IDCStatistics;
class AbsDCPlayersCtx;
class DCInitialize
{
public:
    DCInitialize(AbsDCPlayersCtx *plaCtx, IDCStatistics *statistics,
           IDCMetaContext *metaCtx, IDCIndexController *idxCtrl);
    void init(const QVector<DCPlayer> &playerMds, const DCMeta &meta, const QVector<DCInput> &inputs);
private:
    void initMeta(const DCMeta &meta);
    void initPlayerDetails(const QVector<DCPlayer> &players, const DCMeta &meta);
    void initScores(const QVector<DCInput> &inputs);
    void initStatus();
    QStringList toPlayerNames(const QVector<DCPlayer> &players);
    AbsDCPlayersCtx *_playersContext;
    IDCStatistics *_statistics;
    IDCMetaContext *_metaContext;
    IDCIndexController *_indexController;
};
#endif // DCINITPLAYERSCORES_H
