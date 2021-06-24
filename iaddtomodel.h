#ifndef IADDTOMODEL_H
#define IADDTOMODEL_H

template<typename TModelInterface, typename TValue>
class IAddToModel
{
public:
    typedef TModelInterface ModelInterface;
    typedef TValue Value;
    virtual void add(const ModelInterface *model , const Value &value) = 0;
};

#endif // IADDTOMODEL_H
