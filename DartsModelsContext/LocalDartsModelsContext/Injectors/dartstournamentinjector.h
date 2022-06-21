#ifndef DARTSTOURNAMENTINJECTOR_H
#define DARTSTOURNAMENTINJECTOR_H

template<typename T> class IDbContext;
template<typename T> class IModel;
class QUuid;

class DartsModelsServices;

class DartsTournamentInjector
{
public:
    void injectServices(DartsModelsServices *context);
private:
    IDbContext<IModel<QUuid>> *assembleDbContext();
};
#endif // DARTSTOURNAMENTINJECTOR_H
