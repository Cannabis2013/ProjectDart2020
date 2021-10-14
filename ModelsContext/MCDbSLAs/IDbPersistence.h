#ifndef IDBPERSISTENCE_H
#define IDBPERSISTENCE_H

template <typename TJsonBuilder, typename TModelBuilder>
class IDbPersistence
{
public:
    virtual void fetchModels(const TModelBuilder *modelBuilder) = 0;
    virtual void saveChanges(const TJsonBuilder *jsonBuilder) = 0;
};

#endif // IDBPERSISTENCE_H
