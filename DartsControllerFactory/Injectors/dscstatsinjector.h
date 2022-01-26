#ifndef DSCSTATSINJECTOR_H
#define DSCSTATSINJECTOR_H
class DCServices;
class PlayerStatsSLAs;
class DSCStatsInjector
{
public:
    void inject(DCServices *dc) const;
};

#endif // DSCSTATSINJECTOR_H
