#ifndef ICONNECT
#define ICONNECT

template<typename TFirstInterface,typename TSecondInterface, typename TThirdInterface>
class IConnect
{
public:
    virtual void connectServices(TFirstInterface *,
                                 TSecondInterface *,
                                 TThirdInterface*) = 0;
};

#endif // ICONNECT
