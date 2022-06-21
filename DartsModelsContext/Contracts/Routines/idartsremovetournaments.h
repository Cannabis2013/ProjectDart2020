#ifndef IDARTSREMOVETOURNAMENTS_H
#define IDARTSREMOVETOURNAMENTS_H

class DartsModelsServices;

template<typename T> class QVector;
class IDartsRemoveTournaments
{
public:
    typedef QVector<int> Indexes;
    virtual bool remove(const Indexes &indexes, DartsModelsServices *services) = 0;
};

#endif // IDARTSREMOVETOURNAMENTS_H
