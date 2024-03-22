#ifndef DARTSCONTROLLERS_H
#define DARTSCONTROLLERS_H

class ServiceCollection;
class DartsJsonReport;

class DartsServices {
public:
        ServiceCollection* build();

private:
        void injectPersistences(ServiceCollection* services);
        void injectServices(ServiceCollection* services);
};

#endif // DARTSCONTROLLERS_H
