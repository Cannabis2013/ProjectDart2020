#ifndef PERSISTENCEINTERFACE_H
#define PERSISTENCEINTERFACE_H

class IPersistence
{
public:
    virtual void fetchModels() = 0;
    virtual void saveState() = 0;
};

#endif // PERSISTENCEINTERFACE_H
