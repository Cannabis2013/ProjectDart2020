#ifndef PERSISTENCEINTERFACE_H
#define PERSISTENCEINTERFACE_H

class PersistenceInterface
{
public:
    virtual void loadIntoMemmory() = 0;
    virtual void saveState() = 0;
};

#endif // PERSISTENCEINTERFACE_H
