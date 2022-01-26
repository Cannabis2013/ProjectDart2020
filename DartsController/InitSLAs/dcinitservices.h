#ifndef DCINITSERVICES_H
#define DCINITSERVICES_H
#include "idcinitialize.h"
class DCInitServices
{
public:
    IDCInitialize *loader() const {return _loader;}
    void setLoader(IDCInitialize *service) {_loader = service;}
private:
    IDCInitialize *_loader;
};
#endif // DCINITSERVICES_H
