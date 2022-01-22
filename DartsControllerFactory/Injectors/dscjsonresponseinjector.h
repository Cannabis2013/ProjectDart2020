#ifndef DSCJSONRESPONSEINJECTOR_H
#define DSCJSONRESPONSEINJECTOR_H
class AbstractDCJsonBuilder;
class DCJsonSLAs;
class DSCJsonResponseInjector
{
public:
    void inject(DCJsonSLAs *dc);
private:
    void injectBuilder(AbstractDCJsonBuilder *builder) const;
};

#endif // DCJSONRESPONSEINJECTOR_H
