#ifndef CONTROLLERINITIALIZER_H
#define CONTROLLERINITIALIZER_H

#include <QString>

class ControllerServices;
class ControllerInitializer
{
public:
        ControllerInitializer(ControllerServices* services);

        void init(const QByteArray& json);
        void initFromStorage();
        void reset();
        void saveState();

private:
        ControllerServices* const _services;
};

#endif // CONTROLLERINITIALIZER_H
