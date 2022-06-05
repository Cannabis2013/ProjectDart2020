#ifndef DARTSINPUTINJECTOR_H
#define DARTSINPUTINJECTOR_H

class DartsInputDb;
class DartsModelsServices;
template<typename T> class IModel;
class QUuid;

class DartsInputInjector
{
public:
    void injectServices(DartsModelsServices *context);
private:
    DartsInputDb *assembleDbContext();
};
#endif // DARTSINPUTINJECTOR_H
