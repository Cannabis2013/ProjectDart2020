#ifndef IDARTSSETWINNER_H
#define IDARTSSETWINNER_H
class QString;
class QUuid;
template<typename T>
class QVector;
template<typename TModel>
class IDartsSetWinner
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual void setWinner(const QUuid &tournamentId, const QString &name) const = 0;
};

#endif // IDARTSSETWINNER_H
