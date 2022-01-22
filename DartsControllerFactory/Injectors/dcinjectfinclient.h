#ifndef DCINJECTFINCLIENT_H
#define DCINJECTFINCLIENT_H
class DCFinishBuilder;
class DartsConstructSLAs;
class DCFinishesSLAs;
class DCInjectFinClient
{
public:
    void inject(DCFinishesSLAs *services) const;
private:
    void injectBuilderClient(DCFinishBuilder *builder) const;
    void injectConRowClient(DartsConstructSLAs *service) const;
};

#endif // DCINJECTFINCLIENT_H
