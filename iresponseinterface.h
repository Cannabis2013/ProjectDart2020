#ifndef ISTATUSINTERFACE_H
#define ISTATUSINTERFACE_H
template<typename TArguments>
class IResponseInterface
{
public:
    virtual void handleRequestFromContext(const int &request, const TArguments &args) = 0;
    virtual void handleResponseFromContext(const int &response, const TArguments &args) = 0;
};

#endif // ISTATUSINTERFACE_H
