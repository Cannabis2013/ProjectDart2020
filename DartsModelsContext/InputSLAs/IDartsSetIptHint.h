#ifndef IDARTSSETIPTHINT_H
#define IDARTSSETIPTHINT_H
class QByteArray;
class QString;
class QUuid;
template<typename T>
class QVector;
template<typename TModel>
class IDartsSetIptHint
{
public:
    typedef TModel Model;
    virtual void setHidden(QUuid tournamentID, QString name, const QByteArray &indexByteArray) const = 0;
    virtual void setVisible(QUuid tournamentID, QString name, const QByteArray &indexByteArray) const = 0;
    virtual void setVisible(Model *input) const = 0;
};

#endif // IDARTSSETIPTHINT_H
