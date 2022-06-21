#ifndef ICREATESTATMODEL_H
#define ICREATESTATMODEL_H
class QString;
template<typename TModel>
class ICreateStatModel
{
public:
    virtual TModel create(const QString &name) const = 0;
};
#endif // ICREATEMIRROR_H
