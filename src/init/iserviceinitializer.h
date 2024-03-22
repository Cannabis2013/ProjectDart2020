#ifndef ISERVICEINITIALIZER_H
#define ISERVICEINITIALIZER_H

class QByteArray;
class ServiceCollection;

class IServiceInitializer {
public:
        virtual void init(const QByteArray& json) = 0;
        virtual void initFromStorage() = 0;
        virtual void reset() = 0;
        virtual void saveState() = 0;
};

#endif // ISERVICEINITIALIZER_H
