#ifndef IDARTSPERSIST_H
#define IDARTSPERSIST_H
class IDartsPersist
{
public:
    virtual bool persistTournamentsChanges() = 0;
    virtual bool persistInputChanges() = 0;
    virtual bool persistAllChanges() = 0;
};
#endif // IDARTSPERSIST_H
