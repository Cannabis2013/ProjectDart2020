#ifndef ISTATUSINTERFACE_H
#define ISTATUSINTERFACE_H
template<typename TArguments>
class IStatusInterface
{
public:
    virtual void sendStatus(const int &status, const TArguments &args) = 0;
    virtual void recieveStatus(const int &status, const TArguments &args) = 0;
};

#endif // ISTATUSINTERFACE_H
