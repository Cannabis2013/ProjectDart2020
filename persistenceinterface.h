#ifndef PERSISTENCEINTERFACE_H
#define PERSISTENCEINTERFACE_H

class PersistenceInterface
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
};

#endif // PERSISTENCEINTERFACE_H
