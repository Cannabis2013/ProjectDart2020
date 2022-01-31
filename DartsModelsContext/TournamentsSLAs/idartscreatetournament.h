#ifndef IDARTSCREATETOURNAMENT_H
#define IDARTSCREATETOURNAMENT_H

template<typename T> class QVector;
class QByteArray;
template<typename TModel>
class IDartsCreateTournament
{
public:
    typedef TModel Model;
    typedef QByteArray ByteArray;
    typedef QVector<int> Indexes;
    virtual Model *create(const ByteArray &byteArray, const Indexes &playerIndexes) const = 0;
};

#endif // IDARTSCREATETOURNAMENT_H
