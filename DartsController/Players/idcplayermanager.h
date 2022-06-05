#ifndef IDCPLAYERMANAGER_H
#define IDCPLAYERMANAGER_H

template<typename T> class QVector;
struct DCIndex;
class QString;
class QStringList;

template<typename TPlayer,typename TInput>
class IDCPlayerManager
{
public:
    typedef TPlayer Player;
    typedef TInput Input;
    typedef QVector<Player> Players;
    virtual void reset(const int &initRemScore) = 0;
    virtual Player &player(const QString &name) = 0;
    virtual Player &player(const int &index) = 0;
    virtual Players &players() = 0;
    virtual Players players() const = 0;
    virtual void updateScore(const Input &input) = 0;
    virtual void updateScores(const QVector<Input> &inputs) = 0;
    virtual void addPlayers(const Players &players) = 0;
    virtual bool status(const QString &name) const = 0;
    virtual void updateStatus(const Input &ipt) = 0;
    virtual int count() const = 0;
};
#endif // IDARTSSCORES_H
