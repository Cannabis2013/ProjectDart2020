#ifndef LOCALPERSISTENCEINJECTOR_H
#define LOCALPERSISTENCEINJECTOR_H
class PersistenceSLAs;
class LocalPersistenceInjector
{
public:
    void inject(PersistenceSLAs *context);
};

#endif // LOCALPERSISTENCEINJECTOR_H
