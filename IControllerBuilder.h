#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TParameterFormat>
class IControllerBuilder
{
public:
    typedef TParameterFormat Parameters;
    virtual TControllerInterface *buildDartsController(const Parameters &params) = 0;
};

#endif // ICONTROLLERBUILDER_H
