#ifndef INJECTDPCROUTINES_H
#define INJECTDPCROUTINES_H
class DCServices;
class InjectDPCRoutines
{
public:
    void inject(DCServices *dc);
private:
    void injectInputRoutines(DCServices *dc);
    void injectStatsRoutines(DCServices *dc);
    void injectOtherRoutines(DCServices *dc);
};

#endif // INJECTDPCROUTINES_H
