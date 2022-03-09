#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

class IPersistence
{
public:
    virtual bool saveChanges() = 0;
    virtual void fetch() = 0;
};

#endif // ABSTRACTFILEPERSISTENCE_H
