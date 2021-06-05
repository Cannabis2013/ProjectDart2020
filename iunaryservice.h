#ifndef IJSONEXTRACTOR_H
#define IJSONEXTRACTOR_H

template<typename TInput, typename TOutput>
class IUnaryService
{
public:
    typedef TInput InputType;
    typedef TOutput OutputType;
    virtual OutputType service(InputType input) = 0;
};

#endif // IJSONEXTRACTOR_H
