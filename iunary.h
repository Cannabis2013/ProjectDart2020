#ifndef IJSONEXTRACTOR_H
#define IJSONEXTRACTOR_H

template<typename TInput, typename TOutput>
class IUnary
{
public:
    virtual TOutput service(TInput) = 0;
};

#endif // IJSONEXTRACTOR_H
