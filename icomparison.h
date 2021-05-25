#ifndef ICOMPARISON_H
#define ICOMPARISON_H
template<typename  TModel>

class IComparison{
public:
    virtual bool operator()(const TModel* _first, const TModel* _second) = 0;
};

#endif // ICOMPARISON_H
