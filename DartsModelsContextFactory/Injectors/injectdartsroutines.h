#ifndef INJECTDARTSROUTINES_H
#define INJECTDARTSROUTINES_H
class DartsModelsServices;
class InjectDartsRoutines
{
public:
    void inject(DartsModelsServices *context);
private:
    void injectTournamentRoutines(DartsModelsServices *context);
    void injectInputRoutines(DartsModelsServices *context);
    void injectIndexRoutines(DartsModelsServices *context);
    void injectPersistenceRoutines(DartsModelsServices *context);
};

#endif // INJECTDARTSROUTINES_H
