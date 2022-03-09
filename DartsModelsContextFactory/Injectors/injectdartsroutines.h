#ifndef INJECTDARTSROUTINES_H
#define INJECTDARTSROUTINES_H

class DartsContext;
class DartsModelsRoutines;
class DartsModelsServices;

class InjectDartsRoutines
{
public:
    void inject(DartsContext *context);
private:
    void injectTournamentRoutines(DartsModelsRoutines *context);
    void injectInputRoutines(DartsModelsRoutines *context);
    void injectIndexRoutines(DartsModelsServices *context);
};

#endif // INJECTDARTSROUTINES_H
