#ifndef ISTATUSINTERFACE_H
#define ISTATUSINTERFACE_H
template<typename TArguments>
class IResponseInterface
{
public:
    virtual void transmitResponse(const int &response, const TArguments &args) = 0;
};

#endif // ISTATUSINTERFACE_H
