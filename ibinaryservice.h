#ifndef IBINARY_H
#define IBINARY_H

template<typename TFirstArg, typename TSecondArg, typename TOutput>
class IBinaryService
{
public:
    virtual TOutput service(TFirstArg,TSecondArg) = 0;
};

#endif // IBINARY_H
