#ifndef IDARTSREMOVETOURNAMENTS_H
#define IDARTSREMOVETOURNAMENTS_H
template<typename T> class QVector;
class IDartsRemoveTournaments
{
public:
    typedef QVector<int> Indexes;
    virtual void remove(const Indexes &indexes) = 0;
};

#endif // IDARTSREMOVETOURNAMENTS_H
