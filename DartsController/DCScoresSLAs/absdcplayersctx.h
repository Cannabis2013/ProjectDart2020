#ifndef IDSCSCORESSERVICE_H
#define IDSCSCORESSERVICE_H
template<typename T>
class QVector;
struct DCInput;
struct DCPlayer;
struct DCIndex;
class QString;
class QStringList;
class AbsDCPlayersCtx
{
public:
    typedef QVector<DCPlayer> DartsScoreModels;
    virtual void reset(const int &initRemScore) = 0;
    virtual DCPlayer &player(const QString &name) = 0;
    virtual DCPlayer &player(const DCIndex &idx) = 0;
    virtual DartsScoreModels &players() = 0;
    virtual DartsScoreModels players() const = 0;
    virtual void updateScore(const DCInput &ipt) = 0;
    virtual void updateScores(const QVector<DCInput> &inputs) = 0;
    virtual void set(const QStringList &names, const int &remScore) = 0;
    virtual bool status(const QString &name) const = 0;
    virtual void updateStatus(const DCInput &ipt) = 0;
    virtual int count() const = 0;
};
#endif // IDARTSSCORES_H
