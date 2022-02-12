#ifndef INJECTDSCROUTINES_H
#define INJECTDSCROUTINES_H
class DCServices;
class InjectDSCRoutines
{
public:
    void inject(DCServices *dc);
private:
    void injectInputRoutines(DCServices *dc);
    void injectOtherRoutines(DCServices *dc);
};

#endif // INJECTDSCROUTINES_H
