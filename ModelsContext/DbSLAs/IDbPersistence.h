#ifndef IDBPERSISTENCE_H
#define IDBPERSISTENCE_H
template <typename TJsonBuilder, typename TModelBuilder, typename TResponseFormat>
class IDbPersistence
{
public:
    virtual bool fetch(const TModelBuilder *modelBuilder) = 0;
    virtual TResponseFormat saveChanges(const TJsonBuilder *jsonBuilder) = 0;
};

#endif // IDBPERSISTENCE_H
