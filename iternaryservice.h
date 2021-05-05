#ifndef ITERNARYSERVICE_H
#define ITERNARYSERVICE_H

template<typename TFirst, typename TSecond, typename TThird, typename TReturn>
class ITernaryService
{
public:
    virtual TReturn service(TFirst,TSecond,TThird) = 0;
};

#endif // ITERNARYSERVICE_H
