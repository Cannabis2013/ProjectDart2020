#ifndef CREATEDPC_H
#define CREATEDPC_H

class AbsDartsCtrl;
class DCInjectFinClient;
class CreateDPC
{
public:
    CreateDPC();
    AbsDartsCtrl *create();
private:
    DCInjectFinClient *finInjector;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
