#ifndef DSCSTATSINJECTOR_H
#define DSCSTATSINJECTOR_H
class PlayerStatsSLAs;
class DSCStatsInjector
{
public:
    void inject(PlayerStatsSLAs *dc) const;
};

#endif // DSCSTATSINJECTOR_H
