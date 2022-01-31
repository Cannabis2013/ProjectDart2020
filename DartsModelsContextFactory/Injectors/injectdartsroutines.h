#ifndef INJECTDARTSROUTINES_H
#define INJECTDARTSROUTINES_H
class DMCServices;
class InjectDartsRoutines
{
public:
    void inject(DMCServices *context);
private:
    void injectTournamentRoutines(DMCServices *context);
    void injectInputRoutines(DMCServices *context);
    void injectIndexRoutines(DMCServices *context);
    void injectPersistenceRoutines(DMCServices *context);
};

#endif // INJECTDARTSROUTINES_H
