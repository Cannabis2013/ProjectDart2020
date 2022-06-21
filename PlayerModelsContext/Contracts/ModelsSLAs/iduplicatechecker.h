#ifndef IDUPLICATECHECKER_H
#define IDUPLICATECHECKER_H
template<typename TModel, typename TDbContext>
class IDuplicateChecker
{
public:
    typedef TModel BaseModel;
    typedef TDbContext DbContext;
    virtual bool isDup(BaseModel* player, DbContext *dbContext) const = 0;
};
#endif // IDUPLICATECHECKER_H
