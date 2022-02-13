#ifndef DCINJECTFINCLIENT_H
#define DCINJECTFINCLIENT_H
class DCServices;
class DCFinishBuilder;
class DartsConstructSLAs;
class DCFinishServices;
class DCInjectFinClient
{
public:
    void inject(DCServices *services) const;
private:
    void injectBuilderClient(DCFinishBuilder *builder) const;
    void injectConRowClient(DartsConstructSLAs *service) const;
};

#endif // DCINJECTFINCLIENT_H
