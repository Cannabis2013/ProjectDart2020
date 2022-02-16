#ifndef DARTSINPUTINJECTOR_H
#define DARTSINPUTINJECTOR_H
class DartsModelsServices;
class DartsInputInjector
{
public:
    void injectServices(DartsModelsServices *context) const;
};
#endif // DARTSINPUTINJECTOR_H
