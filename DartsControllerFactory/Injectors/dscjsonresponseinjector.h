#ifndef DSCJSONRESPONSEINJECTOR_H
#define DSCJSONRESPONSEINJECTOR_H
class AbstractDCJsonBuilder;
class DCServices;
class DSCJsonResponseInjector
{
public:
    void inject(DCServices *dc);
private:
    void injectBuilder(AbstractDCJsonBuilder *builder) const;
};

#endif // DCJSONRESPONSEINJECTOR_H
